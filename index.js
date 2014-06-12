var port_fp = process.argv[2];
//var microstepping = process.argv[3] || 16;
var baudrate = process.argv[4] || 9600;

console.log(port_fp)
console.log("--------");
var ledPin = 13;

var firmata = require('firmata');
var board = new firmata.Board(port_fp, function(err){
 if (err) {
        console.log(err);
        return;
    }
  console.log('connected');
  console.log(
    'Firmware: '
    + board.firmware.name
    + '-' + board.firmware.version.major
    + '.' + board.firmware.version.minor);


  var ledOn = true;
  for (var i = 0; i<32; i++) {
    board.pinMode(i, board.MODES.OUTPUT);
  }
  setInterval(function(){
    if (ledOn) {
          console.log('+');
          for (var i = 0; i<32; i++) {
            board.digitalWrite(i, board.HIGH);
          }
    }
    else {
          console.log('-');
          for (var i = 0; i<32; i++) {
            board.digitalWrite(i, board.LOW);
          }
    }

    ledOn = !ledOn;
});
});
