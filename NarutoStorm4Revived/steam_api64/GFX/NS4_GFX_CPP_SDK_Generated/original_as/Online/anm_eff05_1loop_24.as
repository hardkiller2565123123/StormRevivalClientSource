package net_card_fla
{
   import flash.display.MovieClip;
   import flash.events.Event;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol35")]
   public dynamic class anm_eff05_1loop_24 extends MovieClip
   {
      
      public var mc_vortex:MovieClip;
      
      public function anm_eff05_1loop_24()
      {
         super();
         addFrameScript(0,this.frame1);
      }
      
      public function fl_RotateContinuously_5(param1:Event) : *
      {
         --this.mc_vortex.rotation;
      }
      
      internal function frame1() : *
      {
         this.mc_vortex.addEventListener(Event.ENTER_FRAME,this.fl_RotateContinuously_5);
      }
   }
}

