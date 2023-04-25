var baseUrl = 'http://18.222.189.198:5005';
var state="off";
var myname="";
var art_piece="";
var mytoken = "";
var inthandle;
var inthandle2;
var color = '#343a40';

document.addEventListener("click", e => {
    const isDropdownButton = e.target.matches("[data-dropdown-button]")
    if (!isDropdownButton && e.target.closest('[data-dropdown]') != null) return

    let currentDropdown
    if (isDropdownButton) {
        currentDropdown = e.target.closest('[data-dropdown]')
        currentDropdown.classList.toggle('active')
    }

    document.querySelectorAll("[data-dropdown].active").forEach(dropdown => {
        if (dropdown === currentDropdown) return
        dropdown.classList.remove('active')
    })
})

document.addEventListener("DOMContentLoaded", function() {
    setColor(color);
  });

document.getElementById('anger').addEventListener("click", (e) => {
    setColor('red');
})

document.getElementById('sadness').addEventListener("click", (e) => {
    setColor('blue');
})

document.getElementById('joy').addEventListener("click", (e) => {
    setColor('green');
})

document.getElementById('confusion').addEventListener("click", (e) => {
    setColor('cyan');
})


function setColor(color) {
    document.getElementById('navbar').style.backgroundColor = color;}



// ADD COLOR TO DATABASE input.addEventListener('click', ));
      
// apply the event listener to all images
document.querySelectorAll('.emotion-button').forEach((element) => {
	element.addEventListener('click', event => {
		var colorID = event.currentTarget.id;
		addColor(colorID);
	});
});


function completeAddColor(results){
	var art_piece = results['art_piece'];
	var color = results['color'];
// 	mytoken = results['token'];
	console.log("Art: "+art_piece+", Color: "+color);	
}

function addColor(colorID) {
	var art_piece = "Prototype Test";
	fetch(baseUrl+'/response/addColor/'+art_piece+'/'+colorID, {
        method: 'get'
    })
    .then (response => response.json() )
    .then (data =>completeAddColor(data))
    .catch(error => {
        {alert("Error: Something went wrong:"+error);}
    })
}