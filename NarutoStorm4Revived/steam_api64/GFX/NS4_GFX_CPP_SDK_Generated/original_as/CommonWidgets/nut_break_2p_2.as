package duel_break_fla
{
   import flash.display.MovieClip;
   import script.xcmn_tex00.nut_tex00;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol2")]
   public dynamic class nut_break_2p_2 extends MovieClip
   {
      
      public var dmy_msg:nut_tex00;
      
      public function nut_break_2p_2()
      {
         super();
         addFrameScript(14,this.frame15,24,this.frame25);
      }
      
      internal function frame15() : *
      {
         this.stop();
      }
      
      internal function frame25() : *
      {
         this.stop();
      }
   }
}

