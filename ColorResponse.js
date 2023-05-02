var baseUrl = 'http://18.222.189.198:5005';
var state="off";
var art_piece="";
var inthandle;
var inthandle2;
var color = '#343a40';


//Color Page js
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


// DROPDOWN FOR ART PIECE
getAllArts();

function artDropdown(data) { //currently working --tam
	var dropdown = "";
	for (var key in data){
		dropdown += "<option value='"+key+"'>"+data[key]+"<\option>";
	};
	document.querySelector('#slct').innerHTML = dropdown;
	return;
}

function completeGetArts(results){
	if (!results["success"]) {
		// document.querySelector('#output').innerHTML = ErrQuery+": get sites";
		return;
	}
	data = results['all_arts'];
	artDropdown(data);
    }

function getAllArts(){
	fetch(baseUrl+'getAllArts', {
		method: 'get'	
	})
	.then (response => response.json())
    .then (data =>completeGetArts(data))
    .catch(error => {
        {alert("Error: Something went wrong:"+error);}
    })
}


// ADD COLOR TO DATABASE input.addEventListener('click', ));
// apply the event listener to all images
document.querySelectorAll('.emotion-button').forEach((element) => {
	element.addEventListener('click', event => {
		var colorID = event.currentTarget.id;
		var art_piece = document.getElementById('slct').innerHTML;
		addColor(art_piece, colorID);
	});
});

function completeAddColor(results){
	var art_piece = results['art_piece'];
	var color = results['color'];
	console.log("Art: "+art_piece+", Color: "+color);	
}

function addColor(art_piece, colorID) {
	fetch(baseUrl+'/response/addColor/'+art_piece+'/'+colorID, {
        method: 'get'
    })
    .then (response => response.json() )
    .then (data =>completeAddColor(data))
    .catch(error => {
        {alert("Error: Something went wrong:"+error);}
    })
}
