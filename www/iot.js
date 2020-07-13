var my_timer;
var i = 0;
function timer_fun(arg) {
    if (arg == "1")//开启定时器
    {
        //每1秒 就调用一次
        my_timer = setInterval("update_data();", 1000);//定时单位毫秒
    }
    else if (arg == "0")//关闭定时器
    {
        //清除定时器
        clearInterval(my_timer);
    }
}
function my_fun() {
    //Math.random产生一个0~1的随机数浮点数
    //Math.round 四舍五入 取整
    var num = Math.round(Math.random() * 100);
    document.getElementById("temp").innerHTML = num;
    document.getElementById("humi").innerHTML = num + 1;
}

function getXMLHttpRequest() {
    var xmlhttp = null;
    if (window.XMLHttpRequest)//自动检测当前浏览器的版本，如果是IE5.0以上的高版本的浏览器
    {// code for IE7+, Firefox, Chrome, Opera, Safari
        xmlhttp = new XMLHttpRequest();//创建请求对象
    }
    else////如果浏览器是底版本的
    {// code for IE6, IE5
        xmlhttp = new ActiveXObject("Microsoft.XMLHTTP");//创建请求对象
    }
    return xmlhttp;//返回请求对象
}

function update_data() {
    //POST数据是密文传输
    var url = "/cgi-bin/iot.cgi";
    //创建一个xmlHttpRequest对象
    var xmlHttp = null;
    xmlHttp = getXMLHttpRequest();
    var data = "get_data";

    xmlHttp.onreadystatechange = function () {
        //alert(xmlHttp.readyState+"   "+xmlHttp.status)
        if (xmlHttp.readyState == 4 && xmlHttp.status == 200) {
            //获取服务器的结果
            var ret = xmlHttp.responseText;
            //将ret赋值给label
            if (ret != "NULL\n") {
                var arr = ret.split(",");
                document.getElementById("num").innerHTML = i++;
                document.getElementById("temp").innerHTML = arr[0];
                document.getElementById("humi").innerHTML = arr[1];
            }

        }
    }

    //open POST
    xmlHttp.open("POST", url, true);

    //POST send 由于url没有数据 所以只能用send将data发送出去
    xmlHttp.send(data);//将data发送给服务器
}
function set_sys() {
    var temp_min = document.getElementById("temp_min").value;
    var temp_max = document.getElementById("temp_max").value;
    var humi_min = document.getElementById("humi_min").value;
    var humi_max = document.getElementById("humi_max").value;
    //获取下拉列表框被选中的索引号
    var index = document.getElementById("temp_sw").selectedIndex;

    //根据索引号 从选项数据中options[]中得到选中的内容
    var temp_sw = document.getElementById("temp_sw").options[index].value;
    index = document.getElementById("humi_sw").selectedIndex;
    var humi_sw = document.getElementById("humi_sw").options[index].value;

    if (!isNaN(temp_max) && !isNaN(temp_min) && !isNaN(humi_max) && !isNaN(humi_min)) {

        //POST数据是密文传输
        var url = "/cgi-bin/iot.cgi";
        //创建一个xmlHttpRequest对象
        var xmlHttp = null;
        xmlHttp = getXMLHttpRequest();
        var data = "set_data";
        data += ',' + temp_min + ',' + temp_max + ',' + humi_max + ',' + humi_min;
        if (temp_sw == "开启") {
            data += ",manual";
        }
        else if (temp_sw == "关闭") {
            data += ",auto";
        }
        if (humi_sw == "开启") {
            data += ",manual";
        }
        else if (humi_sw == "关闭") {
            data += ",auto";
        }
        xmlHttp.onreadystatechange = function () {
            //alert(xmlHttp.readyState+"   "+xmlHttp.status)
            if (xmlHttp.readyState == 4 && xmlHttp.status == 200) {
                //获取服务器的结果
                var ret = xmlHttp.responseText;
                alert(ret);
            }
        }
        //open POST
        xmlHttp.open("POST", url, true);
        //POST send 由于url没有数据 所以只能用send将data发送出去
        xmlHttp.send(data);//将data发送给服务器

    }
    else {
        alert("请输入数字");
        document.getElementById("temp_min").value = "";
        document.getElementById("temp_max").value = "";
        document.getElementById("humi_min").value = "";
        document.getElementById("humi_max").value = "";
        return;
    }
}

function cls_set() {
    document.getElementById("temp_min").value = "";
    document.getElementById("temp_max").value = "";
    document.getElementById("humi_min").value = "";
    document.getElementById("humi_max").value = "";

}