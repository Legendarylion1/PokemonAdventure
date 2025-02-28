document.getElementById("addBug").
            addEventListener("click", function () {

                const myDiv = document.getElementById('bugDiv');
                myDiv.className = "addition";

                const bugContainer = document.createElement('div');

                const input = document.createElement('input');
                input.type = 'text';
                input.id = 'bugInput_' + myDiv.childElementCount;

                const lineBreak = document.createElement('br');
                lineBreak.id = 'bugLineBreak_' + myDiv.childElementCount;

                const removeButton = document.createElement('button');
                removeButton.id = 'bugRemoveButton_' + myDiv.childElementCount;
                removeButton.textContent = '-';
                removeButton.className = "removeButton";
                removeButton.addEventListener("click", function() {
                    myDiv.removeChild(bugContainer);
                });
            
                bugContainer.appendChild(input);
                bugContainer.appendChild(removeButton);
                bugContainer.appendChild(lineBreak);
            
                myDiv.appendChild(bugContainer);
});

document.getElementById("addPokemon").
    addEventListener("click", function () {

        const myDiv = document.getElementById('pokemonDiv');
        myDiv.className = "addition";

        const pokemonContainer = document.createElement('div');

        const input = document.createElement('input');
        input.type = 'text';
        input.id = 'pokemonInput_' + myDiv.childElementCount;

        const lineBreak = document.createElement('br');
        lineBreak.id = 'pokemonLineBreak_' + myDiv.childElementCount;

        const removeButton = document.createElement('button');
        removeButton.id = 'pokemonRemoveButton_' + myDiv.childElementCount;
        removeButton.textContent = '-';
        removeButton.className = "removeButton";
        removeButton.addEventListener("click", function() {
            myDiv.removeChild(pokemonContainer);
        });
    
        pokemonContainer.appendChild(input);
        pokemonContainer.appendChild(removeButton);
        pokemonContainer.appendChild(lineBreak);
    
        myDiv.appendChild(pokemonContainer);
});

document.getElementById("addFeature").addEventListener("click", function () {

    const myDiv = document.getElementById('featureDiv');

    const featureContainer = document.createElement('div');
    featureContainer.className = "addition";  // Add the addition class

    const featureName = document.createElement('p');
    featureName.className = 'sectionTitle';
    featureName.innerText = 'Name';
    
    const inputName = document.createElement('input');
    inputName.type = 'text';
    inputName.id = 'featureNameInput_' + Date.now();

    const featureDescription = document.createElement('p');
    featureDescription.className = 'sectionTitle';
    featureDescription.innerText = 'Description';
    
    const inputDescription = document.createElement('input');
    inputDescription.type = 'text';
    inputDescription.id = 'featureDescriptionInput_' + Date.now();

    const featureBullets = document.createElement('p');
    featureBullets.className = 'sectionTitle';
    featureBullets.innerText = 'Bullets';

    const bulletDiv = document.createElement('div');

    const addBulletPoint = document.createElement('button');
    addBulletPoint.id = 'featureAddBullet_' + Date.now();
    addBulletPoint.textContent = 'Add Bullet';
    addBulletPoint.addEventListener("click", function() {
        event.preventDefault();
        const innerBulletDiv = document.createElement('div');
        const bulletInput = document.createElement('input');
        bulletInput.type = 'text';
        bulletInput.className = 'bulletInput';

        // Create a remove button for the bullet
        const removeBulletButton = document.createElement('button');
        removeBulletButton.textContent = '-';
        removeBulletButton.className = 'removeBulletButton';
        removeBulletButton.addEventListener('click', function () {
            event.preventDefault();
            bulletDiv.removeChild(innerBulletDiv);
        });

        // Add the bullet input and remove button to the bulletDiv
        innerBulletDiv.appendChild(bulletInput);
        innerBulletDiv.appendChild(removeBulletButton);
        bulletDiv.appendChild(innerBulletDiv);
    });

    const removeButton = document.createElement('button');
    
    removeButton.id = 'featureRemoveButton_' + Date.now();
    removeButton.textContent = 'REMOVE FEATURE';
    removeButton.className = "removeButton";
    removeButton.addEventListener("click", function() {
        event.preventDefault();
        myDiv.removeChild(featureContainer);
    });

    const featureDetails = document.createElement('div');
    featureDetails.className = 'featureDetails';
    featureDetails.style.display = 'block';

    const hiddenButton = document.createElement('button');
    hiddenButton.id = 'featureHiddenButton_' + Date.now();
    hiddenButton.textContent = 'v';

    const hiddenName = document.createElement('h3');
    hiddenName.textContent = 'NEW FEATURE';
    hiddenName.className = 'hiddenName';

    hiddenButton.addEventListener("click", function() {
        event.preventDefault();
        const isExpanded = featureDetails.style.display === 'block';
        //featureDetails.style.display = isExpanded ? 'none' : 'block';  // Toggle visibility

        if (inputName.value === '')
            hiddenName.textContent = 'NEW FEATURE';
        else
            hiddenName.textContent = inputName.value;

        if (isExpanded)
        {
            featureDetails.style.display = 'none';
            hiddenButton.textContent = '^';
            featureContainer.appendChild(hiddenName);
        }
        else
        {
            featureContainer.removeChild(hiddenName);
            featureDetails.style.display = 'block';
            hiddenButton.textContent = 'v';
        }
    });

    // Initially, hide description and bullets
    
    featureDetails.appendChild(featureName);
    featureDetails.appendChild(inputName);
    featureDetails.appendChild(featureDescription);
    featureDetails.appendChild(inputDescription);
    featureDetails.appendChild(featureBullets);
    featureDetails.appendChild(bulletDiv);
    featureDetails.appendChild(addBulletPoint);
    featureDetails.appendChild(document.createElement('br'));
    featureDetails.appendChild(removeButton);

    // Toggle expand/collapse on featureContainer click
    
    featureContainer.appendChild(hiddenButton);
    featureContainer.appendChild(featureDetails);

    myDiv.appendChild(featureContainer);
});


document.getElementById("addMove").
    addEventListener("click", function () {

        const myDiv = document.getElementById('moveDiv');
        myDiv.className = "addition";

        const moveContainer = document.createElement('div');

        const input = document.createElement('input');
        input.type = 'text';
        input.id = 'moveInput_' + myDiv.childElementCount;

        const lineBreak = document.createElement('br');
        lineBreak.id = 'moveLineBreak_' + myDiv.childElementCount;

        const removeButton = document.createElement('button');
        removeButton.id = 'moveRemoveButton_' + myDiv.childElementCount;
        removeButton.textContent = '-';
        removeButton.className = "removeButton";
        removeButton.addEventListener("click", function() {
            myDiv.removeChild(moveContainer);
        });
    
        moveContainer.appendChild(input);
        moveContainer.appendChild(removeButton);
        moveContainer.appendChild(lineBreak);
    
        myDiv.appendChild(moveContainer);
});

function getTrueFalse(id)
{
    if (document.getElementById(id).checked)
        return "true";
    return "false";
}

const getVersion = function()
{
    return document.getElementById("major").value + "." +
    document.getElementById("minor").value + "." +
    document.getElementById("bug").value;
}

const jsonUpdate = function()
{
    //"currentVersion": "0.0.0",
    //"allVersions": ["0.0.0"],
    //"versionChanges" : {
    //    "0.0.0": {
    //        "animations": false,
    //        "dependencies": false,
    //        "images": false,
    //        "shaders": false,
    //        "executable": false,
    //        "dlls": false,
    //        "updater": false
    //    }
    //}

    var version = '"' + getVersion() + '"';

    var data = '"currentVersion": ' + version + ",\n";
    data += '"allVersions": [' + version + '],\n';
    data += '"versionChanges" : {\n';
    data +=  "\t" + version + ": {\n";
    data += '\t\t"animations": ' + getTrueFalse("animations") + ',\n';
    data += '\t\t"dependencies": ' + getTrueFalse("dependencies") + ',\n';
    data += '\t\t"images": ' + getTrueFalse("images") + ',\n';
    data += '\t\t"shaders": ' + getTrueFalse("shaders") + ',\n';
    data += '\t\t"executable": ' + getTrueFalse("executable") + ',\n';
    data += '\t\t"dlls": ' + getTrueFalse("dlls") + ',\n';
    data += '\t\t"updater": ' + getTrueFalse("updater") + ',\n';
    data += "\t}\n";
    data += "}";

    document.getElementById("jsonID").innerText = data;
}

const getMarkdownDescription = function()
{
    return document.getElementById("description").value;
}

const getMarkdownFeatures = function()
{
    return "";
}

const getMarkdownPokemon = function()
{
    return "";
}

const getMarkdownMoves = function()
{
    return "";
}

const getMarkdownBalanceChanges = function()
{
    return "";
}

const getMarkdownBugFixes = function()
{
    return "";
}

const markdownUpdate = function()
{
    //https://github.com/MarketingPipeline/Markdown-Tag
    
    var text = '# Patch Notes v' + getVersion() + '\n';
    text += "\n";
    text += getMarkdownDescription();
    text += getMarkdownFeatures();
    text += getMarkdownPokemon();
    text += getMarkdownMoves();
    text += getMarkdownBalanceChanges();
    text += getMarkdownBugFixes();

    //text += 'Content Check\n';
    //text += '![pokemongif](https://github.com/Legendarylion1/Personal-Projects/assets/74434159/6b69e2d8-7e4a-4a1a-83f7-d1e847e67bb8)';

    const markdownPreview = document.getElementById('markdownID');
    markdownPreview.textContent = text; // Show it in the preview area
    renderMarkdown();
}

document.getElementById("major").addEventListener("input", jsonUpdate);
document.getElementById("minor").addEventListener("input", jsonUpdate);
document.getElementById("bug").addEventListener("input", jsonUpdate);

document.getElementById("major").addEventListener("input", markdownUpdate);
document.getElementById("minor").addEventListener("input", markdownUpdate);
document.getElementById("bug").addEventListener("input", markdownUpdate);

document.getElementById("animations").addEventListener("click", jsonUpdate);
document.getElementById("dependencies").addEventListener("click", jsonUpdate);
document.getElementById("images").addEventListener("click", jsonUpdate);
document.getElementById("shaders").addEventListener("click", jsonUpdate);
document.getElementById("executable").addEventListener("click", jsonUpdate);
document.getElementById("dlls").addEventListener("click", jsonUpdate);
document.getElementById("updater").addEventListener("click", jsonUpdate);





window.onload = function() {
    jsonUpdate();
    markdownUpdate();
};