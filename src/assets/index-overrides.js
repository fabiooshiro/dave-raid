// Show an element.
function showFlexElem(el) {
    if (!el || !el.style) {
        return
    }
    el.style.display = "flex";
}

// Show an element.
function showBlockElem(el) {
    if (!el || !el.style) {
        return
    }
    el.style.display = "block";
}

// Show an element.
function hideElem(el) {
    if (!el || !el.style) {
        return
    }
    el.style.display = "none";
}