window.onload = function () {
	var str=""
      data=[];
      TempData(true);
      HumiData(true);
      UVData(true);
      LightData(true);

      Draw();     
}

  function httpGet(theUrl)
{
    var xmlHttp = new XMLHttpRequest();
    xmlHttp.open( "GET", theUrl, false ); // false for synchronous request
    xmlHttp.send( null );
    return xmlHttp.responseText;
}

  function Text(Jsontext)
  {
    var dejson = JSON.parse(Jsontext);
    var _list = dejson.feeds;
    var text = _list[0];
    var returnTemp = new Array();

    /*for(var i=0;i<100;i++)
    {
        returnTemp[i]=_list[i].field1;
    }*/

    //document.write(returnTemp[20]);
    return _list; 
  }


function Draw() {

var chart = new CanvasJS.Chart("chartContainer",
    {
      zoomEnabled: true,
      zoomType: "xy",
      title:{
        text: "Enable Zooming on X & Y Axis"
      },
       title:{
        text:"Weather Line Chart",
        subtext: "OO"
      },
      legend: {
        horizontalAlign: "right",
        verticalAlign: "center"
      },
      axisY:{
        includeZero: false
      },
      data: data,  // random generator below

   });

    chart.render();
}

  var limit = 100;    //increase number of dataPoints by increasing this
  	var _url = "https://api.thingspeak.com/channels/148353/feeds.json?results=100"
    var DataList = Text(httpGet(_url));
    //document.write(DataList);
    //Process Data

var data = [];

function TempData(chk)
  	{
  		if(chk)
  		{
  			var data1 = []; var dataSeries1 = { type: "line" };
  			var dataPoints1 = [];
  			for (var i = 0; i < limit; i += 1) {
		        if(DataList[i].field1.toUpperCase()=='NAN')
		            tmp = null;
		        else
		            var tmp = parseInt(DataList[i].field1);

	        //document.write(tmp+' ');
	         dataPoints1.push({
	          x: i,
	          y: tmp,
	          lineColor:"orange"
	           });
	        }
	    dataSeries1.dataPoints = dataPoints1;
	    data.push(dataSeries1);
  		}
}

function HumiData(chk){
	if(chk)
	{
		var data2 = []; var dataSeries2 = { type: "line" };
	    var dataPoints2 = [];
	    for (var i = 0; i < limit; i += 1) {
	        if(DataList[i].field2.toUpperCase()=='NAN')
	            tmp = null;
	        else
	            var tmp = parseInt(DataList[i].field2);

	        //document.write(tmp+' ');
	         dataPoints2.push({
	          x: i,
	          y: tmp,
	          lineColor:"red"
	           });
	        }
	     //document.write(dataPoints2[1].y);
	     dataSeries2.dataPoints = dataPoints2;
	    data.push(dataSeries2);
	}
}

function UVData(chk){
	if(chk)
	{
		var data3 = []; var dataSeries3 = { type: "line" };
	    var dataPoints3 = [];
	    for (var i = 0; i < limit; i += 1) {
	        if(DataList[i].field3.toUpperCase()=='NAN')
	            tmp = null;
	        else
	            var tmp = parseInt(DataList[i].field3);

	        //document.write(tmp+' ');
	         dataPoints3.push({
	          x: i,
	          y: tmp,
	          lineColor:"blue"
	           });
	        }
	     //document.write(dataPoints2[1].y);
	     dataSeries3.dataPoints = dataPoints3;
	    data.push(dataSeries3);
	}
}

function LightData(chk){
	if(chk)
	{
		var data4 = []; var dataSeries4 = { type: "line" };
	    var dataPoints4 = [];
	    for (var i = 0; i < limit; i += 1) {
	        if(DataList[i].field4.toUpperCase()=='NAN')
	            tmp = null;
	        else
	            var tmp = parseInt(DataList[i].field4);

	        //document.write(tmp+' ');
	         dataPoints4.push({
	          x: i,
	          y: tmp,
	          lineColor:"green"
	           });
	        }
	     //document.write(dataPoints2[1].y);
	     dataSeries4.dataPoints = dataPoints4;
	    data.push(dataSeries4);
	}
}

    function show(my_form)
     {
      var str=""
      data=[];
      TempData((my_form.check1.checked?true:false));
      HumiData((my_form.check2.checked)?true:false);
      UVData((my_form.check3.checked)?true:false);
      LightData((my_form.check4.checked)?true:false);

      Draw();     
     }