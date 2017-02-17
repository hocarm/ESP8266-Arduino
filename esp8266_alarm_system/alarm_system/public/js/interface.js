$(document).ready(function() {

  // Lấy thông tin từ cảm biến
  function refresh_motion() {
  	$.getq('queue', '/motion', function(data) {
      if (data.state == 0) {$('#motion').html("Khong co nguoi");}
      if (data.state == 1) {

        // Thay đổi thông báo trên giao diện
        $('#motion').html("Co thich khach");

        // Bật âm cảnh báo nếu tùy chọn Bat bao coi
        $.get('/alarm', function(data) {
          if (data.state == 1) {$.playSound('/audio/alarm');}
        });
        
      }	
    });
  }
  refresh_motion();
  setInterval(refresh_motion, 500);

  // Khởi tạo nút tùy chọn cảnh báo âm thanh
  $.get('/alarm', function(data) {
    var alarm_state = data.state;
    
    if (alarm_state == 1) {
      $('#alarm').html("Bat bao coi");
      $('#alarm').attr('class', 'btn btn-block btn-lg btn-success');
    }

    if (alarm_state == 0) {
      $('#alarm').html("Tat bao coi");
      $('#alarm').attr('class', 'btn btn-block btn-lg btn-danger');
    }
  });

  // Kiểm tra khi click chọn vào nút
  $('#alarm').click(function() {

  	// Lấy trạng thái
    $.get('/alarm', function(data) {
    	var alarm_state = data.state;
		
    	if (alarm_state == 0) {
    	  $.post('/alarm?state=1');
    	  $('#alarm').html("Bat bao coi");
        $('#alarm').attr('class', 'btn btn-block btn-lg btn-success');
    	}

    	if (alarm_state == 1) {
    	  $.post('/alarm?state=0');
    	  $('#alarm').html("Tat bao coi");
        $('#alarm').attr('class', 'btn btn-block btn-lg btn-danger');
    	}
    });

  });

});