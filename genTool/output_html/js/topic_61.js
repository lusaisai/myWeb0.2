$( function() {

$('#list286').mouseover(function() {
	$('#topic61 img').attr('src', 'http://img.xiami.com/images/album/img56/23256/3351911246346366_2.jpg');
	$('#topic61 span.listtxt').html('电影看了十几遍，真的很赞，超喜欢里面的音乐。');
	});
$('#list286').click(function() {
	$('#musicPlayer h3').html('妈妈咪呀原声');
	$('#musicPlayer embed').replaceWith('<embed src="http://www.xiami.com/widget/4097932_1768969825,1768969804,1768969805,1768969806,1768969820,1768969801,1768969808,1768969819,1768969814,1768969823,1768969807,1768969816,1768969803,1768969815,1768969800,1768969818,1768969802,1768969809,1768969810,1768969811,1768969812,1768969813,1768969817,1768969822,1768969821,1768969826,1768969827,_235_346_000000_494949_1/multiPlayer.swf" type="application/x-shockwave-flash" width="235" height="346" wmode="opaque"></embed>');
	$('#topic61 li').css('color', '#000000');
	$('#list286').css('color', '#CC0052');
	});

}
)
;
