/*
 * 函  数: dateFormat
 * 功  能: 时间字符串转换函数
 * 参  数: nSeconds [in] 传入的时间值 单位S
 * 返回值: 无
 */

function dateFormat(second){
    var timeTxt="";
    var hh,mm,ss;

    hh = second / 3600 | 0;
    second = Math.round(second) - hh * 3600;
    mm = second / 60 | 0;
    ss = Math.round(second) - mm * 60;

    if(hh!==0)
    {
        if(hh<10)
        {
            timeTxt =   "0"+hh+":";
        }
        else
        {
            timeTxt =   hh+":";
        }
    }
    if(mm<10)
    {
        mm  =   "0"+mm;
    }
    timeTxt =   timeTxt+mm;

    if(ss<10)
    {
        ss  =   "0"+ss;
    }
    timeTxt =   timeTxt+":"+ss;

    return  timeTxt;

  }

