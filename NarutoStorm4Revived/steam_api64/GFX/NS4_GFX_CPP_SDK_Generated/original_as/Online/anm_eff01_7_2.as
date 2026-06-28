package net_card_fla
{
   import flash.display.MovieClip;
   import flash.events.Event;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol6")]
   public dynamic class anm_eff01_7 extends MovieClip
   {
      
      public var mc_eff01_1:MovieClip;
      
      public var mc_eff01_2:MovieClip;
      
      public var mc_eff01_3:MovieClip;
      
      public var mc_eff01_4:MovieClip;
      
      public var mc_eff01_5:MovieClip;
      
      public var mc_eff01_6:MovieClip;
      
      public var mc_eff01_7:MovieClip;
      
      public var mc_eff01_8:MovieClip;
      
      public function anm_eff01_7()
      {
         super();
         addFrameScript(0,this.frame1,6,this.frame7,12,this.frame13,18,this.frame19,24,this.frame25,31,this.frame32,38,this.frame39,44,this.frame45,50,this.frame51);
      }
      
      public function fl_RotateContinuously_9(param1:Event) : *
      {
         this.mc_eff01_1.rotation += 0.5;
      }
      
      public function fl_RotateContinuously_11(param1:Event) : *
      {
         this.mc_eff01_2.rotation -= 0.5;
      }
      
      public function fl_RotateContinuously_10(param1:Event) : *
      {
         this.mc_eff01_3.rotation -= 0.5;
      }
      
      public function fl_RotateContinuously_12(param1:Event) : *
      {
         this.mc_eff01_4.rotation += 0.5;
      }
      
      public function fl_RotateContinuously_13(param1:Event) : *
      {
         this.mc_eff01_5.rotation += 0.5;
      }
      
      public function fl_RotateContinuously_14(param1:Event) : *
      {
         this.mc_eff01_6.rotation -= 0.5;
      }
      
      public function fl_RotateContinuously_15(param1:Event) : *
      {
         this.mc_eff01_7.rotation += 0.5;
      }
      
      public function fl_RotateContinuously_16(param1:Event) : *
      {
         this.mc_eff01_8.rotation -= 0.5;
      }
      
      internal function frame1() : *
      {
         this.mc_eff01_1.addEventListener(Event.ENTER_FRAME,this.fl_RotateContinuously_9);
      }
      
      internal function frame7() : *
      {
         this.mc_eff01_2.addEventListener(Event.ENTER_FRAME,this.fl_RotateContinuously_11);
      }
      
      internal function frame13() : *
      {
         this.mc_eff01_3.addEventListener(Event.ENTER_FRAME,this.fl_RotateContinuously_10);
      }
      
      internal function frame19() : *
      {
         this.mc_eff01_4.addEventListener(Event.ENTER_FRAME,this.fl_RotateContinuously_12);
      }
      
      internal function frame25() : *
      {
         this.mc_eff01_5.addEventListener(Event.ENTER_FRAME,this.fl_RotateContinuously_13);
      }
      
      internal function frame32() : *
      {
         this.mc_eff01_6.addEventListener(Event.ENTER_FRAME,this.fl_RotateContinuously_14);
      }
      
      internal function frame39() : *
      {
         this.mc_eff01_7.addEventListener(Event.ENTER_FRAME,this.fl_RotateContinuously_15);
      }
      
      internal function frame45() : *
      {
         this.mc_eff01_8.addEventListener(Event.ENTER_FRAME,this.fl_RotateContinuously_16);
      }
      
      internal function frame51() : *
      {
         this.stop();
      }
   }
}

