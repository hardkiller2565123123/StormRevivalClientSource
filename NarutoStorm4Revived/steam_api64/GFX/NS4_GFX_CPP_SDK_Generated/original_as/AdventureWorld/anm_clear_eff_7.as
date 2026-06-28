package start_memory_fla
{
   import flash.display.MovieClip;
   import flash.events.Event;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol28")]
   public dynamic class anm_clear_eff_7 extends MovieClip
   {
      
      public var mc_sun1:MovieClip;
      
      public var mc_sun2:MovieClip;
      
      public function anm_clear_eff_7()
      {
         super();
         addFrameScript(0,this.frame1);
      }
      
      public function fl_RotateContinuously_6(param1:Event) : *
      {
         this.mc_sun2.rotation -= 0.5;
      }
      
      internal function frame1() : *
      {
         this.mc_sun2.addEventListener(Event.ENTER_FRAME,this.fl_RotateContinuously_6);
      }
   }
}

