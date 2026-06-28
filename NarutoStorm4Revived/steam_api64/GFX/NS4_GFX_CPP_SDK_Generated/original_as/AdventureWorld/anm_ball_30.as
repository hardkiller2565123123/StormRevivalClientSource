package freebtl_cp_fla
{
   import flash.display.MovieClip;
   import flash.events.Event;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol69")]
   public dynamic class anm_ball_30 extends MovieClip
   {
      
      public var mc_ball:MovieClip;
      
      public function anm_ball_30()
      {
         super();
         addFrameScript(0,this.frame1);
      }
      
      public function fl_RotateContinuously_4(param1:Event) : *
      {
         this.mc_ball.rotation += 0.2;
      }
      
      internal function frame1() : *
      {
         this.mc_ball.addEventListener(Event.ENTER_FRAME,this.fl_RotateContinuously_4);
      }
   }
}

