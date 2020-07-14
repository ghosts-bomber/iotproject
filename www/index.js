function login()
{
    var user = document.getElementById("user").value;
    var passwd = document.getElementById("passwd").value;
    var url="/cgi-bin/login.cgi";
    var data="";
    data = "login"+" "+user+" "+passwd;

    //alert(data);
    var xmlHttp=null;
    xmlHttp = getXMLHttpRequest();
    xmlHttp.onreadystatechange=function()
    {
        //alert(xmlHttp.readyState +" "+ xmlHttp.status);
        if(xmlHttp.readyState == 4 && xmlHttp.status==200)
        {
            var ret = xmlHttp.responseText;
            if(ret=="successful\n")
            {
                window.location.href='display.html';
            }
            else
            {
                document.getElementById("passwd").value="";
                alert(ret);
            }
        }
    }
   
    xmlHttp.open("POST",url,true);
    xmlHttp.send(data);
    
}

function getXMLHttpRequest()
{
    var xmlhttp=null;
    if(window.XMLHttpRequest)
    {
        xmlhttp=new XMLHttpRequest();
    }
    else{
        xmlhttp = new ActiveXObject("Microsoft.XMLHTTP");
    }
    return xmlhttp;
}

