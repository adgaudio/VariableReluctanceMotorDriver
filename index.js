var port_fp = process.argv[2];
//var microstepping = process.argv[3] || 16;
var baudrate = process.argv[4] || 9600;

console.log(port_fp)
console.log("--------");

var firmata = require('firmata');
var board = new firmata.Board(port_fp, function(err){
 if (err) {
   console.log('failed');
   console.log(err);
   return;
 }
 console.log('connected');
 console.log(
   'Firmware: '
   + board.firmware.name
   + '-' + board.firmware.version.major
   + '.' + board.firmware.version.minor);

	board.on('string',function(string){
		console.log(string);
	});

   setInterval(function(){
       console.log('+');
       for (var i = 0; i<32; i++) {
         board.analogWrite(1, 1);
       }
   }, 1);
});

console.log("hi");
console.log(board.pins);

