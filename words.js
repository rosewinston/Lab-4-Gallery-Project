window.onload = function(argument) {
	var baseUrl = 'http://18.222.189.198:5005';
	var wordsRetrieved = "";
	var words = {};
	var words_attr = [];
	
	var canvas = document.getElementById('c');
	canvas.width = window.innerWidth;
	canvas.height = window.innerHeight;

	if (canvas.getContext) {
		var c = canvas.getContext('2d'),
			w = canvas.width,
			h = canvas.height;

		c.strokeStyle = 'red';
		c.lineWidth = 5;

		fetchWords(); 
		console.log(wordsRetrieved);
		

	
		console.log(words);
		function fetchWords() {
			const date = new Date();
			let currentDay= String(date.getDate()).padStart(2, '0');
			let currentMonth = String(date.getMonth()+1).padStart(2,"0");
			let currentYear = date.getFullYear();
			// format date: year - month - date 
			let currentDate = `${currentYear}-${currentMonth}-${currentDay}`;
			console.log("Current Date: " + currentDate); 
			
			
			timestamp = "2023-05-05";
   			fetch(baseUrl + '/retrieve/words/'+timestamp, {
   			method: 'get'
   			})
   			.then(response => response.json())
   			.then(data => formatWords(data))
   			.catch(error => {
   	 		{alert("Error: Something went wrong:" + error); }
  	 		})

   		}
		console.log(words);
		function formatWords(data){
			var result = data;
			var formattedString = "";
			var first = true; 
			if (result["status"]=="success"){
				var wordList = result["words"]; 
				wordList.forEach(function (wordElement) {
					if (first){
						formattedString+=wordElement; 
						first = false; 
					}else{
						formattedString+=" " + wordElement; 
					}
					
				});
				console.log(typeof formattedString); 
				console.log(typeof moby);
				wordsRetrieved = formattedString; 
				console.log(typeof wordsRetrieved);
				string_handle(wordsRetrieved);
			}else{
				alert("Error: Word Cloud Retrieve Failed"); 
			}
		}
		
		//function to randomly assign a color to a given word 
		function colorAssign(){
			//color options from IBM Design Colorblind Friendly Palette
			var colorArray = ['#648FFF', '#785EF0', '#DC267F', '#FE6100', '#FFB000'];
			var colorRand = colorArray[Math.floor(Math.random()* 5)]; 
			return colorRand; 
		}
		
		
		//for (key in words) {	
			//words_attr.push(new Word(key));
		//}
		
		// constructor
		Word = function(key) {
			this.text = key;
			this.x = Math.random() * w;
			this.y = Math.random() * h;
			this.font = words[key] * 50 + 'px arial'
			this.speed = (words[key]);
			this.color = colorAssign();
		}
		
		//check to see if words are being constructed and passed successfully
		console.log(words_attr.length);
		console.log(words);

		function animation() {
			for (var i = 0; i < words_attr.length; i++) {
				c.font = words_attr[i].font;
				c.fillText(words_attr[i].text, words_attr[i].x, words_attr[i].y);
				words_attr[i].width = c.measureText(words_attr[i].text).width;
				c.fillStyle = words_attr[i].color; 
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
	console.log(words);
	function string_handle(str) {
    var lamda = 1;
		var word_array = str.split(" ");
		console.log(typeof word_array);
		
    // Give each word a random occurance counrt
		for (var i = 0; i < word_array.length; i++) {
      var u = Math.random();
      occurance =  -Math.log(u)/(lamda);
      // Should set. this to the number of occurances of word
			words[word_array[i]] = occurance;
		}
	
		for (key in words) {	
			words_attr.push(new Word(key));
		}
		
		return words;
	}

}
