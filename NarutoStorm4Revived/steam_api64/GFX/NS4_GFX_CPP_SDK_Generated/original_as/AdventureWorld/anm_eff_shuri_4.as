package freebtl_cp_fla
{
   import flash.display.MovieClip;
   import flash.events.Event;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol4")]
   public dynamic class anm_eff_shuri_4 extends MovieClip
   {
      
      public var mc_shuri:MovieClip;
      
      public function anm_eff_shuri_4()
      {
         super();
         addFrameScript(0,this.frame1);
      }
      
      public function fl_RotateContinuously_9(param1:Event) : *
      {
         this.mc_shuri.rotation += 0.1;
      }
      
      internal function frame1() : *
      {
         this.mc_shuri.addEventListener(Event.ENTER_FRAME,this.fl_RotateContinuously_9);
      }
   }
}

