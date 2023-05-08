var baseUrl = 'http://18.222.189.198:5005';
var state="off";
var graph = 0;
var unique_arts

summaryEmotion();

function listToMatrix(list, elementsPerSubArray) {
    var matrix = [], i, k;
    for (i = 0, k = -1; i < list.length; i++) {
      if (i % elementsPerSubArray === 0) {
        k++;
        matrix[k] = [];
      }
      matrix[k].push(list[i]);
    }
    return matrix;
}

function getCol(matrix, col){
    var column = [];
    for(var i=0; i<matrix.length; i++){
        column.push(matrix[i][col]);
    }
    return column;
}


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
	
	var unique_arts = arts.filter((item, i, ar) => ar.indexOf(item) === i);
	var unique_emotions = emotions.filter((item, i, ar) => ar.indexOf(item) === i);
	var mat = listToMatrix(counts, unique_arts.length);
	
	var ctx = document.getElementById('chart').getContext('2d');
	
	var chart = new Chart(ctx, {
		type: 'bar',
		data: {
			labels: unique_arts,
			datasets: [{
			
			}]
		}
	})
	
	
	
}