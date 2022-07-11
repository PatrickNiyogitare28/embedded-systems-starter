/*Defining the HTTP Request Starts*/
var request = false;
if (window.XMLHttpRequest) {
    request = new XMLHttpRequest();
}
else if (window.ActiveXObject) {
    request = new ActiveXObject('Microsoft.XMLHTTP');
}
/*Defining the HTTP Request Ends*/

/*
function getIP(json){
    saveBrowsingLogs(json.ip); 
}
*/

function saveBrowsingLogs(){
    var current_url = "<?php echo $current_url ?>";
    current_url = encodeURIComponent(current_url);
    
    console.log(current_url+"\n"); /*For the sake of debugging*/
    
    if (request){
        request.open('POST', 'instances/logObj.php', true);
        request.setRequestHeader("Content-type", "application/x-www-form-urlencoded");
        request.send("current_url="+current_url+"&action=save_browsing_logs");
        
    }
}

saveBrowsingLogs();