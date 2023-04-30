//Admin Portal for Gund Gallery ArtDB
var contactList = [];
const baseUrl = 'http://18.222.189.198:5005';


/* Set up events */
$(document).ready(function() {
	// Add a click event for the filter button
	document.querySelector("#filter-btn").addEventListener("click", (e) => {
		var searchStr = 	document.querySelector("#search").value;
    	findMatches(searchStr);
	});

    $(".dropdown-menu li a").click(function() {
        var selection = $(this).text();
        $(this).parents(".btn-group").find('.btn').html(selection + ' <span class="caret"></span>');
    });

	findMatches(" ");

});

/* Search and display art functions */

// Build output table from comma delimited list
function formatMatches(json) {

    var result = '<table class="table table-success table-striped""><tr><th>First</th>';
    json.forEach(function(entry, i) {
        result += "<tr><td class='first'>" + entry['first']  + "</td>";
        result += "<td><button type='button' class='btn btn-primary btn-sm edit' data-bs-toggle='modal' data-bs-target='#editContact' ";
        result += "onclick=\"editName(" + i + ")\">Edit</button> ";
        result += "<button type='button' class='btn btn-primary btn-sm ' onclick=\"deleteContact("+ entry['ID'] +")\">Delete</button></td></tr>";
    });
    result += "</table>";

    return result;
}

function displayMatches(results) {

    artList = results["results"];
    console.log("Results:"+JSON.stringify(artList));
    document.getElementById("searchresults").innerHTML = formatMatches(artList);
    
}

function findMatches(search) {
	// only include / after find if search not empty
	search = search.trim();
    if (search != "") search = "/" + search;

	console.log("Search:" + search);
    fetch(baseUrl + '/art/find' + search, {
            method: 'get'
        })
        .then(response => response.json())
        .then(json => displayMatches(json))
        .catch(error => {
            {
                alert("Find Error: Something went wrong:" + error);
            }
        })
}

/* Add art piece functions */
function processAdd(results) {
    console.log("Add:", results["status"]);
    document.getElementById("addname").value = "";

    findMatches(" ");

}

function addArtPiece() {
    console.log("Attempting to add an entry");
    console.log("Firstname:" + $('#addname').val());
    $('#searchresults').empty();
    fetch(baseUrl + '/art/add/' + $('#addname').val() + "/", {
            method: 'get'
        })
        .then(response => response.json())
        .then(json => processAdd(json))
        .catch(error => {
            {
                alert("Add Error: Something went wrong:" + error);
            }
        })
}


function editContact(row) {
    console.log("start edit data: "+row+JSON.stringify(contactList[row]));

    console.log("Name of record: " + contactList[row]["name"]);
    editid = contactList[row]["ID"];

	document.getElementById("editname").value = contactList[row]["name"];
	
	//Save ID in modal
	var modal = document.querySelector("#editContact");
	modal.setAttribute("editid",editid);

}


function updateContact() {

	// Get ID in the modal
	var modal = document.querySelector("#editContact");
	id = modal.getAttribute("editid");
	
    console.log("Attempting to edit an entry:"+id); 

    fetch(baseUrl + '/art/update/' + id + '/' + document.getElementById("editname").value, {
                method: 'get'
            })
        .then(alert("Record for " + document.getElementById("editname").value + " updated"))
        .catch(error => {
            {
                alert("Edit Error: something went wrong:" + error);
            }
        });
        
    findMatches(" ");

}


function deleteContact(id) {

    console.log("Attempting to delete an entry:" + id);
    fetch(baseUrl + '/art/delete/' + id, {
            method: 'get'
        })
        .then(alert("Deleted Record: " + id))
        .catch(error => {
            {
                alert("Delete Error: Something went wrong:" + error);
            }
        });
     findMatches(" ");

}