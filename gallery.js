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



// ADD COLOR TO DATABASE input.addEventListener('click', ));
      
// apply the event listener to all images
document.querySelectorAll('.emotion-button').forEach((element) => {
	element.addEventListener('click', event => {
		var colorID = event.currentTarget.id;
		addColor(colorID);
	});
});

function artDropdown(data) {
    var dropdown = '<a class="dropdown-item" href="#" value="0">Select Art Piece</a>';
    for(var key in data) {
		dropdown += '<a class="dropdown-item" href="#" value="'+key+'">'+data[key]+'</a>';
    };
    document.querySelector('#searchtype').innerHTML = dropdown;
    return;
}

function proccessData(results) {
	if (!results["success"]) {
		document.querySelector('#output').innerHTML = ErrQuery+": get sites";
		return;
	}
    data=results['message'];
    artDropdown(data);
}

// Make call to fetch all site names and MAC addresses
function getArt() {
	// Clear the previous results
    document.querySelector('#output').innerHTML = "";
    fetch(baseUrl+"retrieve/art_pieces", {
	method: 'get'
    })
	.then (response => response.json() )
        .then (data => processSites(data))
	.catch(error => {
	    document.querySelector('#output').innerHTML = ErrSrv+": get sites";
	})

}

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

function addWord(word) {
	fetch(baseUrl+'/response/addWord/'+word, {
        method: 'get'
    })
    .then (response => response.json() )
    .then (data =>completeAddWord(data))
    .catch(error => {
        {alert("Error: Something went wrong:"+error);}
    })
}

function completeAddWord(results){
	var word = results['word'];
	console.log("Word: "+word);	
}


//
