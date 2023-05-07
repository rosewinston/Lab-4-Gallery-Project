var baseUrl = 'http://18.222.189.198:5005';
var state="off";
var art_piece="";
var color = '#343a40';

summaryEmotion();

function summaryEmotion(){
	fetch(baseUrl+'/response/summaryEmotion', {
		method: 'get'	
	})
	.then (response => response.json())
    .then (data => completeEmotionResult(data))
    .catch(error => {
        {alert("Error: Something went wrong:"+error);}
    })
}