  function httpGet(theUrl)
{
    var xmlHttp = new XMLHttpRequest();
    xmlHttp.open( "GET", theUrl, false ); // false for synchronous request
    xmlHttp.send( null );
    return xmlHttp.responseText;
}

  function Test(Jsontext)
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


window.onload = function () {

var chart = new CanvasJS.Chart("chartContainer",
    {
      zoomEnabled: true,
      zoomType: "xy",
      title:{
        text: "Enable Zooming on X & Y Axis"
      },
       title:{
        text:"Temperature",
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

var chart = new CanvasJS.Chart("chartContainer2",
    {
      zoomEnabled: true,
      zoomType: "xy",
      title:{
        text: "Enable Zooming on X & Y Axis"
      },
       title:{
        text:"Humidity",
        subtext: "OO"
      },
      legend: {
        horizontalAlign: "right",
        verticalAlign: "center"
      },
      axisY:{
        includeZero: false
      },
      data: data2,  // random generator below

   });

    chart.render();
}
  var limit = 100;    //increase number of dataPoints by increasing this

  var _url = "https://api.thingspeak.com/channels/148353/feeds.json?results=100"
    var DataList = Test(httpGet(_url));
    //document.write(DataList);
    //Process Data

    var data = []; var dataSeries = { type: "line" };
    var dataPoints = [];
    for (var i = 0; i < limit; i += 1) {
        if(DataList[i].field1.toUpperCase()=='NAN')
            tmp = null;
        else
            var tmp = parseInt(DataList[i].field1);

        //document.write(tmp+' ');
         dataPoints.push({
          x: i,
          y: tmp,
          lineColor:"orange"
           });
        }
    dataSeries.dataPoints = dataPoints;
    data.push(dataSeries);

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
    data2.push(dataSeries2);
