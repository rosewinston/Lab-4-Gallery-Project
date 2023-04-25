var baseUrl = 'http://18.222.189.198:5005';
var state="off";
var myname="";
var art_piece="";
var mytoken = "";
var inthandle;
var inthandle2;

document.getElementsByClassName('').addEventListener("click", (e) => {
	color(this.id);
	// generateToken();
});

function completeAddColor(result){
// 	var status = result['status'];
// 	if (status != "success") {
// 		alert("Username or password is incorrect!");
// 		leaveSession();
// 		return;
// 	}
	var art_piece = results['art_piece'];
	var color = results['color'];
// 	mytoken = results['token'];
	console.log("Art: "+user+", Color: "+color);	
}

function addColor(clicked_id) {
	var art_piece = "Prototype Test";
	fetch(baseUrl+'/gallery/addColor/'+art_piece+'/'+clicked_id, {
        method: 'get'
    })
    .then (response => response.json() )
    .then (data =>completeAddColor(data))
    .catch(error => {
        {alert("Error: Something went wrong:"+error);}
    })
}