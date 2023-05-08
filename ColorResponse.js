var baseUrl = 'http://18.222.189.198:5005';
var state="off";
var art_piece="";
var inthandle;
var inthandle2;
var color = '#343a40';
var currentArt = "";



// DROPDOWN FOR ART PIECE
getAllArts();

function siteDropdown(data) { //currently working --tam
	var dropdown = "";
	var countValue = 0;
	data.forEach(function(key){
		dropdown += "<option value='"+countValue+"'>"+key+"</option>";
		countValue += 1;
	})
// 	for (var key in data){
// 		dropdown += "<option value='"+key+"'>"+data[key]+"<\option>";
// 	};
	console.log(dropdown);
	document.querySelector('#slct').innerHTML = dropdown;
	return;
}

function completeGetArts(results){
	if (results["status"] != "success") {
		// document.querySelector('#output').innerHTML = ErrQuery+": get sites";
		return;
	}
	data = results['arts'];
	siteDropdown(data);
}

function getAllArts(){
	fetch(baseUrl+'/response/getAllArts', {
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
		var e = document.getElementById('slct');
		currentArt = e.options[e.selectedIndex].text;
		addColor(art_piece, colorID);
	});
});

function completeAddColor(results){
	var art_piece = results['art_piece'];
	var color = results['color'];
	console.log("Art: "+art_piece+", Color: "+color);	
}

function addColor(currentArt, colorID) {
	fetch(baseUrl+'/response/addColor/'+currentArt+'/'+colorID, {
        method: 'get'
    })
    .then (response => response.json() )
    .then (data =>completeAddColor(data))
    .catch(error => {
        {alert("Error: Something went wrong:"+error);}
    })
}


// CHANGE IMAGE CAROUSEL IMAGE
