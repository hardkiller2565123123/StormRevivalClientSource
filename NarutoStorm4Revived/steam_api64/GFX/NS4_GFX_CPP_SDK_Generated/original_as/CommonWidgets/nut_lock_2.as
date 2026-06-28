package duel_lock_fla
{
   import flash.display.MovieClip;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol18")]
   public dynamic class nut_lock_2 extends MovieClip
   {
      
      public function nut_lock_2()
      {
         super();
         addFrameScript(30,this.frame31,38,this.frame39,69,this.frame70,100,this.frame101,131,this.frame132,162,this.frame163,172,this.frame173,182,this.frame183);
      }
      
      internal function frame31() : *
      {
         gotoAndPlay("loop");
      }
      
      internal function frame39() : *
      {
         gotoAndPlay("loop");
      }
      
      internal function frame70() : *
      {
         gotoAndPlay("mlt_1_loop");
      }
      
      internal function frame101() : *
      {
         gotoAndPlay("mlt_2_loop");
      }
      
      internal function frame132() : *
      {
         gotoAndPlay("mlt_3_loop");
      }
      
      internal function frame163() : *
      {
         gotoAndPlay("mlt_x_loop");
      }
      
      internal function frame173() : *
      {
         this.stop();
      }
      
      internal function frame183() : *
      {
         this.stop();
      }
   }
}

