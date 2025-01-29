// cinnamon.js v0.01
// (c)2024 CinnamonWolfy, Under MPL 2.0

"use strict"

const cinnamonMainSystem = {
    milliseconds: 0,
    keyboard: [ "", -1 ],
    systemRuntimeId: undefined,
    KBHandler: function(event){
        if(event.type = "keyup")
            this.keyboard = [ "", -1 ];
        else if(event.type = "keydown")
            this.keyboard = [ event.key, event.keyCode ];

        event.preventDefault();
    },
    init: function(){
        this.systemRuntimeId = setInterval(function(){cinnamonMainSystem.milliseconds++}, 1);
        window.addEventListener("keydown", this.KBHandler, true);
        window.addEventListener("keyup", this.KBHandler, true);
    }
};

const cinnamonCanvasSystem = {
    canvas: undefined,
    canvasContext: undefined,
    camera2D : {
        x: 0,
        y: 0
    },
    init: function(element){
        this.canvas = element;
        this.canvasContext = element.getContext("2d");
    },
    move: function(x = 0, y = 0){
        this.camera2D.x = x;
        this.camera2D.y = y;
    },
    relMove: function(x = 0, y = 0){
        this.camera2D.x += x;
        this.camera2D.y += y;
    },
    updateCameraPos: function(){
        this.canvasContext.setTransform(1, 0, 0, 1, this.camera2D.x, this.camera2D.y);
    },
    clear: function(){
        this.canvasContext.clearRect(this.camera2D.x, this.camera2D.y, this.canvas.width, this.canvas.height);
    },
    setTextStyle: function(color, font, size){
        this.canvasContext.fillStyle = String(color);
        this.canvasContext.font = String(size) + " " + font;
    },
    print: function(message, x, y, color, font = "Courier New", size = "12px"){
        this.setTextStyle(color, font, size);
        this.canvasContext.fillText(message, x, y);
    }
};

const cinnamonTexture = {
    imgObject: undefined,
    sizeOfFrame: {
        width: 0,
        height: 0
    },
    position: {
        x: 0,
        y: 0,
        degrees: 0
    },
    currentFrameStart: {
        x: 0,
        y: 0
    },
    init: function(src, width, height){
        this.imgObject = new Image();
        this.imgObject.src = src;
        this.sizeOfFrame.width = width;
        this.sizeOfFrame.height = height;
    },
    setPosition: function(x = 0, y = 0, degrees = 0){
        this.position.x = x;
        this.position.y = y;
        this.position.degrees = degrees;
    },
    setPosRel: function(x = 0, y = 0, degrees = 0){
        this.position.x += x;
        this.position.y += y;
        this.position.degrees += degrees;
    },
    setFrame: function(num = 0){
        let tempX = 0, tempY = 0, frameNum = 0;
        for(let i = 0; i < num; i++){
            tempX += this.sizeOfFrame.width;
            if(tempX > this.imgObject.naturalWidth){
                tempX = 0;
                tempY += this.sizeOfFrame.height;
                if(tempY > this.imgObject.naturalHeight){
                    tempY = 0;
                    return 0;
                }
            }
            frameNum++;
        }

        this.currentFrameStart.x = tempX;
        this.currentFrameStart.y = tempY;
        return frameNum
    },
    draw: function(){
        if(this.position.degrees != 0){
            cinnamonCanvasSystem.canvasContext.translate(this.position.x + (this.sizeOfFrame.x / 2), this.position.y + (this.sizeOfFrame.y / 2));
            cinnamonCanvasSystem.canvasContext.rotate(this.position.degrees * (Math.PI / 180));
            cinnamonCanvasSystem.canvasContext.translate(-(this.position.x + (this.sizeOfFrame.x / 2)), -(this.position.y + (this.sizeOfFrame.y / 2)));
        }

        cinnamonCanvasSystem.canvasContext.drawImage(this.imgObject, this.currentFrameStart.x, this.currentFrameStart.y, this.sizeOfFrame.width, this.sizeOfFrame.height, this.position.x, this.position.y, this.sizeOfFrame.width, this.sizeOfFrame.height);

        if(this.position.degrees != 0){
            cinnamonCanvasSystem.canvasContext.translate(this.position.x + (this.sizeOfFrame.x / 2), this.position.y + (this.sizeOfFrame.y / 2));
            cinnamonCanvasSystem.canvasContext.rotate(-this.position.degrees * (Math.PI / 180));
            cinnamonCanvasSystem.canvasContext.translate(-(this.position.x + (this.sizeOfFrame.x / 2)), -(this.position.y + (this.sizeOfFrame.y / 2)));
        }
    }
};