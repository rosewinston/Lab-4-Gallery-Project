var baseUrl = 'http://18.222.189.198:5005';
var state="off";
var art_piece="";
var inthandle;
var inthandle2;
var color = '#343a40';
var currentArt = "";
var gundUrl = 'https://collection.gundgallery.org/Media/images/'



// DROPDOWN FOR ART PIECE
getAllArts();

function siteDropdown(artList, artLink) { //currently working --tam
	var dropdown = "";
	var countValue = 0;
	artList.forEach(function(key){
		dropdown += "<option value='"+countValue+"'>"+key+"</option>";
		// imageList += "<img id='"+
// 		<img id="slide-1" src="gund_img/gund1.jpeg" alt="img" draggable="false">
		countValue += 1;
	})
	
	var imageList = "";
	var count2 = 0;
	artLink.forEach(function(key){
		imageList += "<img id='"+key+"' src='"+gundUrl+key+"' alt='img' draggable='false'>";
	})

	console.log(imageList);
	document.querySelector('#slct').innerHTML = dropdown;
	document.querySelector('.slider').innerHTML = imageList;
	return;
}

function completeGetArts(results){
	if (results["status"] != "success") {
		// document.querySelector('#output').innerHTML = ErrQuery+": get sites";
		return;
	}
	artList = results['arts'];
	artLink = results['links'];
	siteDropdown(artList, artLink);
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
document.querySelectorAll('.link').forEach(element => {
	element.addEventListener('click', event => {
		var emojiGrid = document.getElementsByClassName('slider');
		event.currentTarget.id;
		var e = document.getElementById('slct');
		currentArt = e.options[e.selectedIndex].text;
		console.log(currentArt);
		addColor(currentArt, emoID);
	});
});

// 

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

var dropdownBar = document.getElementsByClassName("slider")[0];

dropdownBar.addEventListener("change", function() {
	
});



// CHANGE IMAGE CAROUSEL IMAGE
