var baseUrl = 'http://18.222.189.198:5005';
var state="off";
var myname="";
var art_piece="";
var mytoken = "";
var inthandle;
var inthandle2;
var color = '#343a40';
var username = "";
var password = "";
var word = ""; 

// LANDING PAGE JS

// Get the modal
var modal = document.getElementById('admin');

// When the user clicks anywhere outside of the modal, close it
window.onclick = function(event) {
    if (event.target == modal) {
        modal.style.display = "none";
    }
}

document.getElementById('admin-join').addEventListener("click", adminLogin);

function completeLogin(data) {
    var status = results['status'];
    if (status != "success") {
        alert("Incorrect Username or Password");
        return;
    }
    else {
        window.location.href = "AdminPortal/AdminPortal.html";
    }
}

function adminLogin() {
   username = document.getElementById('uname').value;
   password = document.getElementById('pword').value;
   fetch(baseUrl + 'admin/join/' + username + '/' + password, {
    method: 'get'
   })
   .then(response => response.json())
   .then(data => completeLogin(data))
   .catch(error => {
    {alert("Error: Something went wrong:" + error); }
   })
}

//

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



document.getElementById('submit-btn').addEventListener("click", getWord);

function getWord() {
   word = document.getElementById('word-response').value;
   fetch(baseUrl + '/response/'+word, {
    method: 'get'
   })
   .then(response => response.json())
   .then(data => completeGetWord(data))
   .catch(error => {
    {alert("Error: Something went wrong:" + error); }
   })
}


function completeGetWord(results){
	var word = results['word'];
	console.log("Word: "+word);	
}


//
