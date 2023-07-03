import React, { useState, useEffect } from 'react';
import axios from 'axios';
import dayjs from 'dayjs';
import { AdapterDayjs } from '@mui/x-date-pickers/AdapterDayjs';
import { DateTimePicker } from '@mui/x-date-pickers/DateTimePicker';
import { LocalizationProvider } from '@mui/x-date-pickers';
import { GraphFunc } from './GraphFunc.js'

if (window.location.origin === "http://localhost:3000") {
  axios.defaults.baseURL = "http://127.0.0.1:8000";
} else {
  axios.defaults.baseURL = window.location.origin;
}

function formatData(data, lower, upper){
  var tmp = {tempPoints: [], humPoints: []};

  data.forEach(element => {
    var date = new Date(element.date);
    
    if(lower !== undefined && upper !== undefined){
      var epochTime = date.getTime();
      
      if(upper < epochTime || epochTime < lower){
        return;
      }
    }

    tmp.tempPoints.push({y: Number(element.temp), x: date})
    tmp.humPoints.push({y: Number(element.hum), x: date})
  });
  return tmp;
}

export function Graph() {

  const [data, getData] = useState('')
  const [startDate, setStartValue] = useState(dayjs());
  const [endDate, setEndValue] = useState(dayjs());
  const [oldStart, setOldStart] = useState(dayjs());
  const [oldEnd, setOldEnd] = useState(dayjs());
  
  useEffect(() => {
    getAllData(undefined, undefined);
  }, []);

  const getAllData = (lower, upper) => {
    axios.get("/api/dhts/")
        .then((res) => {
          const d = formatData(res.data, lower, upper)
          getData(d);
        })
        .catch((err) => console.log(err));
  }

  function handleChanges(e){
    if(startDate.$d.getTime() === oldStart.$d.getTime() && endDate.$d.getTime() === oldEnd.$d.getTime()){
      return
    }
    
    setOldStart(startDate);
    setOldEnd(endDate);

    getAllData(startDate.$d.getTime(), endDate.$d.getTime());
  }


  return(
    <>
      <GraphFunc data={data} />

      <div style={{display: "flex", alignItems: "center", justifyContent: "center",}}>
          <strong style={{marginBottom: 7, marginTop: 7}}>Pick dates for displaying data</strong>
      </div>  

      <LocalizationProvider dateAdapter={AdapterDayjs}>
        <div style={{display: "flex", alignItems: "center", justifyContent: "center",}}>
            <DateTimePicker value={startDate} onChange={setStartValue} onClose={handleChanges} label="Start date" />
            <DateTimePicker value={endDate} onChange={setEndValue} onClose={handleChanges} label="End date" />
        </div>  
      </LocalizationProvider>  
    </>
  )
}
