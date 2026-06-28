package cutin_msion_fla
{
   import flash.display.MovieClip;
   import flash.events.Event;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol34")]
   public dynamic class anm_uzumaki_loop_20 extends MovieClip
   {
      
      public var mc_uzumaki:MovieClip;
      
      public function anm_uzumaki_loop_20()
      {
         super();
         addFrameScript(0,this.frame1);
      }
      
      public function fl_RotateContinuously_7(param1:Event) : *
      {
         --this.mc_uzumaki.rotation;
      }
      
      internal function frame1() : *
      {
         this.mc_uzumaki.addEventListener(Event.ENTER_FRAME,this.fl_RotateContinuously_7);
      }
   }
}

