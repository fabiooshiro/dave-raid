/**
 * Basic template for creating applications with Eitri.
 */

// Importing the communication module with the Host App
import Eitri from "eitri-bifrost";

export default function Home(props) {

    /**
     * Similar to React, you can implement functionalities after the screen has
     * rendered or when specific dependencies change using useEffect. 
     */
    useEffect(() => {

        /**
         * Since we are using JavaScript here, you can use log messages like this
         * one below and track the log through your terminal.
         */
        console.log("This is an Eitri message", props);
    }, []);


    /**
     * You can also create functions at the root of the page class. These functions can be
     * assigned in the Views file.
     */
    const makeRequest = async () => {
        /**
         * Similar to what we do with the Axios library, you can also make
         * an HTTP call to an API. In this example, we are just loading a list of
         * products in JSON format to be used later.
         */
        const {data} = await Eitri.http.get('https://calindra.tech/eitri/product_list.json');

        console.log("Data obtained in HTTP call:", data);
    };


    return (
        <Window bottomInset backgroundColor="neutral-100" statusBarTextColor="white">
            <View>
                
            </View>
        </Window>
    )
}

