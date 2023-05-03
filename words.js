var baseUrl = 'http://18.222.189.198:5005';

window.onload = function(argument) {
	var words = [];
	var wordsRetrieved = fetchWords(words); 
	//var moby = "anger a fear sadness disgust enjoyment happiness love relief contentment amusement joy pride excitement peace satisfaction lonely heartbroken gloomy disappointed hopeless grieved unhappy lost troubled resigned miserable worried doubtful nervous anxious terrified panicked horrified desperate confused stressed annoyed frustrated peeved contrary bitter infuriated irritated mad cheated vengeful insulted dislike revulsion loathing disapproving offended horrified uncomfortable nauseated disturbed withdrawn aversion";
	var words_attr = [];
	string_handle(wordsRetrieved);
	
	
	function fetchWords(words) {
		// default timestamp, change later
		timestamp = "2023-05-01";
   		fetch(baseUrl + '/retrieve/words/'+timestamp, {
   		method: 'get'
   		})
   		.then(response => response.json())
   		.then(data => formatWords(words, data))
   		.catch(error => {
   	 	{alert("Error: Something went wrong:" + error); }
  	 	})
   	}
	
   	function formatWords(words, data){
		var result = data;
		var formattedString = "";
		var first = true; 
	 	if (result["status"]=="success"){
			var wordList = result["words"]; 
			wordList.forEach(function (word) {
				//if (first){
					//formattedString+=word; 
					//first = false; 
				//}else{
					//formattedString+=" " + word; 
				//}
				words.push(word);
    			});
			//return formattedString; 
		}else{
			alert("Error: word cloud retrieve failed, possibly no words"); 
		}
	}
		




	

	var canvas = document.getElementById('c');
	canvas.width = window.innerWidth;
	canvas.height = window.innerHeight;

	if (canvas.getContext) {
		var c = canvas.getContext('2d'),
			w = canvas.width,
			h = canvas.height;

		c.strokeStyle = 'red';
		c.fillStyle = 'white';
		c.lineWidth = 5;

		// constructor
		Word = function(key) {
			this.text = key;
			this.x = Math.random() * w;
			this.y = Math.random() * h;
			this.font = words[key] * 50 + 'px arial'
			this.speed = (words[key]);
		}
		for (key in words) {
			words_attr.push(new Word(key));
		}
		console.log(words_attr.length);

		function animation() {
			for (var i = 0; i < words_attr.length; i++) {
				c.font = words_attr[i].font;
				c.fillText(words_attr[i].text, words_attr[i].x, words_attr[i].y);
				words_attr[i].width = c.measureText(words_attr[i].text).width;
				c.stroke();
			}
			move();
		}

		function move() {
			for (var i = 0; i < words_attr.length; i++) {
				if (words_attr[i].x > w) {
					words_attr[i].x = -words_attr[i].width;
					words_attr[i].y = Math.random()*h;
				}else{
					words_attr[i].x += words_attr[i].speed;
				}
			}
		}

		setInterval(function() {
			c.clearRect(0,0,w,h);
			animation();
		},24);

	}

	function string_handle(str) {
    var lamda = 1;
		//var word_array = str.split(" ");
    // Give each word a random occurance counrt
		for (var i = 0; i < word_array.length; i++) {
      var u = Math.random();
      occurance =  -Math.log(u)/(lamda);
      // Should set. this to the number of occurances of word
			words[word_array[i]] = occurance;
      console.log(occurance);
		}
		return words;
	}

}
