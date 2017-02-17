// Chọn Expressjs
var express = require('express');
var app = express();

// Khai báo port
var port = 3000;

// Biến cho cảm biến chuyển động
var motion = 0;

// Trạng thái ban đầu của cảnh báo
var alarm = 0;

// Hiển thị jade
app.set('view engine', 'jade');

// Cài public folder
app.use(express.static(__dirname + '/public'));

// Đưa ra giao diện
app.get('/', function(req, res){
  res.render('interface');
});

// Thay đổi trạng thái cảm biến cd
app.post('/motion', function(req, res) {
  motion = req.query.state;
  res.send('Data received: ' + motion);
});

// Lấy trạng thái cảm biến cd
app.get('/motion', function(req, res) {
  res.json({state: motion});
});

// Lấy trạng thái báo động
app.get('/alarm', function(req, res) {
  res.json({state: alarm});
});

// Thay đổi trạng thái báo động
app.post('/alarm', function(req, res) {
  alarm = req.query.state;
  res.send('Data received: ' + alarm);
});

// Khởi động server
app.listen(port);
console.log("Listening on port " + port);