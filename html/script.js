
function showPopup() {
    alert("Thank you! Your recommendation has been added.");
}

document.getElementById("recommendation-form")
    .addEventListener("submit", function(event) {
        event.preventDefault();

        const input = document.getElementById("recommendation-text");
        const recommendation = input.value.trim();

        if (recommendation === "") {
            return;
        }

        const newCard = document.createElement("div");
        newCard.className = "recommendation";
        newCard.textContent = '"' + recommendation + '"';

        // Add the new recommendation without deleting existing ones.
        document.getElementById("recommendation-list")
            .appendChild(newCard);

        input.value = "";

        showPopup();
    });
