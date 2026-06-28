package duel_boss_help_fla
{
   import flash.display.MovieClip;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol4")]
   public dynamic class anm_help_pick_4 extends MovieClip
   {
      
      public function anm_help_pick_4()
      {
         super();
         addFrameScript(0,this.frame1,34,this.frame35,45,this.frame46);
      }
      
      internal function frame1() : *
      {
      }
      
      internal function frame35() : *
      {
         gotoAndPlay("loop");
      }
      
      internal function frame46() : *
      {
         this.stop();
      }
   }
}

