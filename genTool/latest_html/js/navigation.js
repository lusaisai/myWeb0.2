$(function() {
 
 $('#nav a').stop().animate({'marginLeft':'-110px'},1500);
 
 $('#nav > li').hover(
  function () {
   $('a',$(this)).stop().animate({'marginLeft':'-2px'},200);
  },
  function () {
   $('a',$(this)).stop().animate({'marginLeft':'-110px'},200);
  }
 );
 
 $('.list li').mousedown( function() {
	$(this).css('box-shadow','none');
	}
).mouseup( function() {
	$(this).css('box-shadow','1px 1px 2px 1px #5F9FFF');
	}
)
;

 $('#randomListen li').mousedown( function() {
	$(this).css({'box-shadow' :'none', 'color': 'lightgreen'});
	}
).mouseup( function() {
	$(this).css({'box-shadow':'1px 1px 2px 1px #5F9FFF', 'color' : 'white'});
	}
)
;

$('#randomListen li').click(function() {
	$('#musicPlayer').load("randomListen.php");
	});

var $scrollingDiv = $("#left_panel");
var end = $(document).height();
 
$(window).scroll(function(){
	offset = $(window).scrollTop();
	if ( $.trim($("#searchResult").text()) == "" && (offset + 900 <= end ) ) {
   $scrollingDiv.stop().animate({"marginTop": offset + "px"}, "slow" );
}
});

$(".list > li").click(function(){
	offset = $(window).scrollTop();
	if ( $.trim($("#searchResult").text()) == "" && (offset + 900 <= end ) ) {
   $scrollingDiv.stop().animate({"marginTop": offset + "px"}, "slow" );
}
}
);

});
