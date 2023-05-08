var baseUrl = 'http://18.222.189.198:5005';
var state="off";

summaryEmotion();
var graph;

function summaryEmotion(){
	fetch(baseUrl+'/response/summaryEmotion', {
		method: 'get'	
	})
	.then (response => response.json())
    .then (data => graphEmotion(data))
    .catch(error => {
        {alert("Error: Something went wrong:"+error);}
    })
}

function graphEmotion(result){
	var arts = result['arts'];
	var emotions = result['emotions'];
	var counts = result['counts'];
	
	let unique_arts = arts.filter((item, i, ar) => ar.indexOf(item) === i);
	console.log(unique_arts);
	let unique_emotions = emotions.filter((item, i, ar) => ar.indexOf(item) === i);

		
	const ctx = document.getElementById('chart3');
	graph = new Chart(ctx, {
		type = 'bar',
		data = {
			labels: unique_arts;
			datasets: [{
				label = unique_emotions[0],
				backgroundColor: "#caf270",
				data: counts;
			}]
		}
	});
}