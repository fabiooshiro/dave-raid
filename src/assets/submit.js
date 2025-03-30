import { createWalletClient, toHex, createPublicClient, custom, http, fromHex, isHex, sha256, keccak256, parseAbi, toFunctionSelector, parseAbiParameters, encodeAbiParameters, publicActions } from 'https://esm.sh/viem@2.23.2'
import { anvil, base, baseSepolia, sepolia } from "https://esm.sh/viem@2.23.2/chains";
import { Parser } from "https://esm.sh/expr-eval@2.0.2";

const RULE_ID_BYTES = 20;

const envClient = {
    NETWORK_CHAIN_ID: "0x14a34", // base Sepolia
    // NETWORK_CHAIN_ID: "0xAA36A7",
    APP_ADDR: "0xECB28678045a94F8b96EdE1c8203aDEa81F8AAe3",
    // WORLD_ADDR: "0x04969e1d36d43515cc6493a286021b44b0fce6f2",
    WORLD_ADDR: "0x872932915526c7bB835ed986784f4F115C903e8c",
};

const contestInfo = {
    "id": "721f735bbca3721f735bbca3cfee7c08a98f4b56",
    "name": "default",
    "description": "",
    "cartridge_id": "721f735bbca3",
    "created_by": "0x5d2a261a2d936659fffee1a218561afc2d5ea034",
    "created_at": 0,
    "input_index": -1,
    "args": "",
    "in_card": "",
    "score_function": "score",
    "tags": [
        "default",
        "args: '', score_function: 'score', incard hash: e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855"
    ],
    "allow_tapes": false,
    "allow_in_card": false,
    "save_tapes": false,
    "save_out_cards": false,
    "tapes": []
};

window.addEventListener("message", messageHandler, false);

function messageHandler(e) {
    const params = e.data;
    if (params.rivemuOnFinish) {
        sendGamePlay(contestInfo, params);
    }
}

async function submitGameplay(walletClient, inputData) {
    const verificationFunctionName = "core.register_external_verification";
    // const verificationFunctionName = "core.verify";
    const verificationParameters = "bytes32,bytes32,bytes,int,bytes32[],bytes";
    const humanMiscAbi = [
        "function addInput(address _app, bytes payload) payable",
    ];

    const miscAbi = parseAbi(humanMiscAbi);

    const inputPayload = encodeAbiParameters(
        parseAbiParameters(verificationParameters), // 'bytes32,bytes32,bytes,int,bytes32[],bytes'
        [
            inputData.rule_id,
            inputData.outcard_hash,
            inputData.tape,
            BigInt(inputData.claimed_score),
            inputData.tapes,
            inputData.in_card,
        ]
    );

    const selector = toFunctionSelector(`${verificationFunctionName}(${verificationParameters})`);
    const payload = selector + inputPayload.replace('0x', '');

    // const payloadTest = encodeFunctionData({
    //   abi: miscAbi,
    //   functionName: 'addInput',
    //   args: [envClient.APP_ADDR, payload],
    // })

    // const payload = encodeFunctionData({
    //   functionName: 'core.register_external_verification',
    //   abi: miscAbi,
    //   args: [inputData.rule_id, inputData.outcard_hash, inputData.tape, inputData.claimed_score, inputData.tapes, inputData.in_card],
    // })

    const publicClient = connectPublicClient();
    const [address] = await walletClient.requestAddresses();

    const { request } = await publicClient.simulateContract({
        account: address,
        address: envClient.WORLD_ADDR,
        abi: miscAbi,
        functionName: 'addInput',
        args: [envClient.APP_ADDR, payload],
        value: BigInt(0)
    });
    const txHash = await walletClient.writeContract(request);

    await publicClient.waitForTransactionReceipt({ hash: txHash });
}

function connectPublicClient() {
    // Declare a Public Client
    const publicClient = createPublicClient({
        chain: getChain(envClient.NETWORK_CHAIN_ID),
        transport: http()
    })

    // Return the public client
    return publicClient;
}

async function sendGamePlay(contestInfo, gameplayResult) {
    const walletClient = await connectWalletClient();
    const score = calculateScore(contestInfo.score_function, gameplayResult.outcard);
    if (!confirm(`Send score ${score}?`)) {
        return
    }
    const inputData = {
        rule_id: formatRuleIdToBytes(contestInfo.id),
        outcard_hash: '0x' + gameplayResult.outhash,
        tape: toHex(gameplayResult.tape),
        claimed_score: score || 0,
        tapes: [],
        in_card: '0x'
    };
    await submitGameplay(walletClient, inputData);
}

function calculateScore(scoreFunction, outcard) {
    const parser = new Parser();
    const scoreFunctionEvaluator = parser.parse(scoreFunction);
    const decoder = new TextDecoder("utf-8");
    if (scoreFunctionEvaluator && decoder.decode(outcard.slice(0, 4)) == 'JSON') {
        const outcard_str = decoder.decode(outcard);
        const outcard_json = JSON.parse(outcard_str.substring(4));
        console.log({ outcard_json })
        return scoreFunctionEvaluator.evaluate(outcard_json);
    }
    return 0;
}
function ruleIdFromBytes(id) {
    return id.startsWith('0x') ? id.slice(2, 2 + 2 * RULE_ID_BYTES) : id.slice(0, 2 * RULE_ID_BYTES);
}

function formatRuleIdToBytes(id) {
    return `0x${ruleIdFromBytes(id)}${'0'.repeat(2 * (32 - RULE_ID_BYTES))}`;
}

const chains = {};
chains[baseSepolia.id] = baseSepolia;
chains[base.id] = base;
chains[anvil.id] = anvil;
chains[sepolia.id] = sepolia;

function getChain(chainId) {
    if (typeof chainId === "string") {
        if (!isHex(chainId)) return null;
        chainId = fromHex(chainId, "number");
    }

    const chain = chains[chainId];
    if (!chain) {
        alert('Chain not found:' + chainId)
        return null;
    }

    return chain;
}

async function connectWalletClient() {
    // Check for window.ethereum
    // window.ethereum is an object provided by MetaMask or other web3 wallets
    let transport;
    if (window.ethereum) {
        // If window.ethereum exists, create a custom transport using it
        transport = custom(window.ethereum);
    } else {
        // If window.ethereum is not available, throw an error
        const errorMessage =
            "MetaMask or another web3 wallet is not installed. Please install one to proceed.";
        throw new Error(errorMessage);
    }

    // Declare a Wallet Client
    // This creates a wallet client using the chain and the custom transport
    const walletClient = createWalletClient({
        chain: getChain(envClient.NETWORK_CHAIN_ID),
        transport: transport,
    }).extend(publicActions);

    // Return the wallet client
    return walletClient;
}