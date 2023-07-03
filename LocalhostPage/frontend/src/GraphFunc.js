import React from 'react';
import CanvasJSReact from '@canvasjs/react-charts';

export function GraphFunc(props){

    const options = {
    zoomEnabled: true,
    animationEnabled: true,
    animationDuration: 1500,
    title: {
        text: "Graph to view sensordata"
    },

    toolTip: {
        shared: true,
        contentFormatter: function(e){
            var content = " ";
            for (var i = 0; i < e.entries.length; i++) {
                content += e.entries[i].dataSeries.name 
                        + " " + "<strong>" 
                        + e.entries[i].dataPoint.y + "</strong>";
                content += "<br/>";
            }
            content += e.entries[0].dataPoint.x + "<br/>";
            return content
        }
    },

    data: [
    {
        type: "line",
        name: "Temperature",
        showInLegend: true,
        dataPoints: props.data?.tempPoints
    },
    {
        type: "line",
        name: "Humidity",
        showInLegend: true,
        dataPoints: props.data?.humPoints
    }]
}

    if (!props.data.humPoints || !props.data.tempPoints) return "Loading";
    return(
    <div>
        <CanvasJSReact.CanvasJSChart options={options} />
    </div>
    )
}