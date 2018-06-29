var banner = document.getElementById('banner');
var legal = document.getElementById('roll-cta');


var tl = new TimelineMax({repeat:0, repeatDelay:2.7});


window.onload = function() {   
    
    tl.set(banner, {visibility: "visible"})

      /*frame one*/	
      .from(".bg, .dell-logo-w, .dell-text-1, .vendor-logo, .funding-text", 0, {alpha:0, ease:Linear.easeIn, delay:0}, "frame1-in")
	  .from(".frame-1-text-1", .5, {alpha:0,  y:-10, ease:Power4.easein}, "frame1-in" )
	  .from(".frame-1-text-2", .5, {alpha:0,  x:-10, ease:Power4.easein}, "frame1-in" )
	  .from(".frame-1-text-2-up1", .5, {alpha:0,  x:-10, ease:Power4.easein}, "frame1-in" )	  
	  .from(".frame-1-text-2-up", .5, {alpha:0,  x:-10, ease:Power4.easein}, "frame1-in" )
	  .from(".frame-1-text-3", .5, {alpha:0,  x:10, ease:Power4.easein}, "frame1-in" )
	  .from(".cta", .5, {alpha:0, ease:Power4.easein}, "frame1-in" )
      .to(".cta, .bg, .dell-logo-w, .dell-text-1, .frame-1-text-1, .frame-1-text-2, .frame-1-text-3, .frame-1-text-2-up, .frame-1-text-2-up1, .funding-text", .3, {alpha:0, ease:Power4.easeout, delay:2.7}, "frame1-out")

      
	  
	  /*frame two*/
	  .from(".main-badge", .5, {alpha:0, y:-10, ease:Linear.easeIn}, "frame2-in")
	  .from(".product1", .5, {alpha:0, x:-202, ease:Linear.easeIn}, "frame2-in")
	  .from(".dell-logo, .cta2, .frame-2-pname, .scrn-size", .5, {alpha:0, ease:Linear.easeIn}, "frame2-in")
      .to(".main-badge, .frame-2-pname, .product1", .3, {alpha:0, ease:Power4.easeout, delay:1.5}, "frame2-out")

  	  /*frame three*/
  	  .from(".frame-3-pname, .product2",  .5, {alpha:0, ease:Power4.easeIn}, "frame3-in")
  	  .from(".frame-3-text-1",  .5, {alpha:0, y:-10, ease:Linear.easeIn}, "frame3-in")
	  .to(".scrn-size", .3,{x:75, y:30, ease:Power4.easeout}, "frame3-out")    
	  .to(".frame-3-pname, .product2, .frame-3-text-1", .3,{alpha:0, ease:Power4.easeout, delay:2}, "frame3-out")
	  
	  /*frame four*/
      .to(".scrn-size", .3,{x:95, y:20, ease:Power4.easeout}, "frame4-out")    
     .from(".funding-text2, .frame-4-text-1, .product3", .5, {alpha:0, ease:Power4.easein}, "frame4-in")
     .from(".frame-4-text", .5, {alpha:0, x:105, ease:Power4.easein}, "frame4-in")
     /*.to(".frame-4-text-1, .product3", .3,{alpha:0, ease:Power4.easeout, delay:2.4})*/    
     .to(".frame-4-text-1, .frame-4-text4, .frame-4-text2, .product3", .3,{alpha:0, ease:Power4.easeout, delay:2.4})

   	  /*frame five*/
      /*.to(".violator", .3,{alpha:0, ease:Power4.easeout}, "frame5-out")*/
      .to(".frame-4-text", .3,{x:0, y:-5, ease:Power4.easeout}, "frame5-out")    
      .to(".scrn-size", .3,{x:-20, y:5, ease:Power4.easeout}, "frame5-out")    
     .from(".badge-last, .funding-text3, .frame-5-text-1, .product4, .frame-5-pname, .frame-5-text, .shipping, .violator, .vendor-logo2", .5, {alpha:0, ease:Power4.easein}, "frame5-in")
     .from(".frame-5-text_box ", .5, {alpha:0, x:100, ease:Power4.easein}, "frame5-in")

	 
   //tl.seek(10).pause(8);
    
  	  /*roll over
	  .from("#roll-cta", .5, {alpha:0, x:-300, ease:Power4.easeout}, "frame5-in")
	  .from("#rolltext", .5, {alpha:0, ease:Power4.easeout}, "frame5-in")
	  .from("#legal-text", .5, {alpha:0, ease:Power4.easeout}, "frame5-in")
	  .from("#flex_bg", .5, {alpha:0, x:-300, ease:Power4.easeout}, "frame5-in")
	  
  	  legal.addEventListener("mouseover",legalHover);
		  function legalHover(){
		  tl.pause();
		  TweenMax.to("#legal", .5, {top:0, ease:Power1.easeOut})  
	  }
	  
	  legal.addEventListener("mouseout",legalOut);
		  function legalOut(){
		  tl.play();
		  TweenMax.to("#legal", .5, {top:-1000, ease:Power1.easeIn})
	  }*/

	  ;
	  
    // tl.seek("loop")

    var currentDuration = tl.duration();
    console.log(currentDuration);   
};