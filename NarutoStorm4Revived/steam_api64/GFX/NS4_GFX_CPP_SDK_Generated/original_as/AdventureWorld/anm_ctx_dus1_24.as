package gametitle_fla
{
   import flash.display.MovieClip;
   import flash.events.Event;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol81")]
   public dynamic class anm_ctx_dus1_24 extends MovieClip
   {
      
      public var mc_msk:MovieClip;
      
      public function anm_ctx_dus1_24()
      {
         super();
         addFrameScript(0,this.frame1);
      }
      
      public function fl_RotateContinuously_4(param1:Event) : *
      {
         this.mc_msk.rotation += 0.1;
      }
      
      internal function frame1() : *
      {
         this.mc_msk.addEventListener(Event.ENTER_FRAME,this.fl_RotateContinuously_4);
      }
   }
}

