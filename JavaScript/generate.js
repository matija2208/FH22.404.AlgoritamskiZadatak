var dim = 1000;
var Trougli = []; //niz trougla za fraktal


var canvas = document.getElementById("canvas");
var context = canvas.getContext("2d");

var Trougao = {
    //osnovni trougao
    Boja:  "black",
    //stranica
    di: dim,
    //tacka A
    Ay: canvas.height,
    Ax: 0,
    //tacka B
    By: canvas.height,
    Bx: dim,
    //tacka C
    Cy: canvas.height - (Math.sqrt(3)*dim)/2,
    Cx: dim/2
};

Trougli.push(Trougao); //napraviti osnovni trougao koji se deli

function crtajTrougao(t){
    context.beginPath();
    //konstruisi trougao A->B->C->A
    context.moveTo(t.Ax, t.Ay);
    context.lineTo(t.Bx, t.By);
    context.lineTo(t.Cx, t.Cy);
    context.lineTo(t.Ax, t.Ay);
    
    context.fillStyle = t.Boja;
    context.fill();

    context.closePath();
};

function fractal() {
    context.clearRect(0, 0, canvas.width, canvas.height);
    for (var i in Trougli) {
        if (Trougli[i].Boja == "black") {
            var Trougao = {
                Boja: "white",
                //dimenzije stranice
                di: Trougli[i].di/2,

                //koord. tacke A
                Ax: (Trougli[i].Ax+Trougli[i].Cx)/2,
                Ay: (Trougli[i].Ay+Trougli[i].Cy)/2,
                    
                //koord. tacke B
                Bx: (Trougli[i].Bx+Trougli[i].Cx)/2,
                By: (Trougli[i].By+Trougli[i].Cy)/2,
                
                //koord. tacke C
                Cx: Trougli[i].Cx,
                Cy: Trougli[i].Cy+(Math.sqrt(3)*Trougli[i].di)/2
            };
            Trougli.push(Trougao);
            
            // desni trougao
            var Trougao = {
                Boja: "black",
                di: Trougli[i].di/2,

                Ax: (Trougli[i].Ax+Trougli[i].Bx)/2,
                Ay: (Trougli[i].Ay+Trougli[i].By)/2,
                

                Bx: Trougli[i].Bx,
                By: Trougli[i].By,
                

                Cx: (Trougli[i].Cx+Trougli[i].Bx)/2,
                Cy: (Trougli[i].Cy+Trougli[i].By)/2
            };
            Trougli.push(Trougao);

            // levi trougao
            var Trougao = {
                Boja: "black",
                di: Trougli[i].di/2,

                Ax: Trougli[i].Ax,
                Ay: Trougli[i].Ay,
                
                Bx: (Trougli[i].Bx+Trougli[i].Ax)/2,
                By: (Trougli[i].By+Trougli[i].Ay)/2,
                
                Cx: (Trougli[i].Cx+Trougli[i].Ax)/2,
                Cy: (Trougli[i].Cy+Trougli[i].Ay)/2
            };
            Trougli.push(Trougao);

            // gornji trougao
            var Trougao = {
                Boja:  "black",
                di: Trougli[i].di/2,

                Ax: (Trougli[i].Ax+Trougli[i].Cx)/2,
                Ay: (Trougli[i].Ay+Trougli[i].Cy)/2,
                
                Bx: (Trougli[i].Bx+Trougli[i].Cx)/2,
                By: (Trougli[i].By+Trougli[i].Cy)/2,
                
                Cx: Trougli[i].Cx,
                Cy: Trougli[i].Cy
            };
            Trougli.push(Trougao);
        }    
    }

    for (var i in Trougli) { //nacrtaj svaki trougao u nizu, sa ovim novim koje smo dodali
            crtajTrougao(Trougli[i]); 
    }   
};

function runFractal(depth){ //cisto provera da li je nivo = 0
    if(depth == 0){
        crtajTrougao(Trougli[0]);
    }

    for(var i = 0;i< depth;i++){
        fractal();
    }
}

function setDepth(){ //uzimanje nivoa iz URL, <URL>?Nivo
    var url_array = document.URL.split('?')
    var depth = url_array[url_array.length-1]; //pokupi iz URl nivo
    document.getElementById("numInput").value = depth;
    runFractal(depth);
}

window.onload = setDepth(); //odmah proveri nivo