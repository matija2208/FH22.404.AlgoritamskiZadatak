const destination = "SjerpinskiTrougao.html"

function gotoRender(id){
    location.href = destination + "?" + id;
}

function valid(){
    const pattern = new RegExp('^\d+$');
    var id = document.getElementById("numInput").value;
    if(pattern.test(id) == false && id>=0){
        gotoRender(id);
    }else{
        alert("Uneli ste nevazeci nivo fraktala!\nNivo moze samo biti ceo broj veci ili jednak nuli.");
    }
}

function checkFirstTime(){
    if(window.location.href.indexOf("?") == -1){
        console.log("lol");
        location.href = destination + "?" + 0;
    }
}

window.onload = checkFirstTime(); //proveriti da li je stranica prazna