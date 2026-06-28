package map_sm_brt_fla
{
   import flash.display.MovieClip;
   import flash.events.Event;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol76")]
   public dynamic class anm_brt_eff1_17 extends MovieClip
   {
      
      public var mc_eff:MovieClip;
      
      public function anm_brt_eff1_17()
      {
         super();
         addFrameScript(0,this.frame1);
      }
      
      public function fl_RotateContinuously_6(param1:Event) : *
      {
         this.mc_eff.rotation += 50;
      }
      
      internal function frame1() : *
      {
         this.mc_eff.addEventListener(Event.ENTER_FRAME,this.fl_RotateContinuously_6);
      }
   }
}

