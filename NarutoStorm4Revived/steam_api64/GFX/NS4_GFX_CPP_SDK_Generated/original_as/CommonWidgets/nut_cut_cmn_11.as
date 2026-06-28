package duel_cutin_fla
{
   import flash.display.MovieClip;
   import script.duel_cutin_lang.nut_duel_msg;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol24")]
   public dynamic class nut_cut_cmn_11 extends MovieClip
   {
      
      public var all_cutin_msg:nut_duel_msg;
      
      public function nut_cut_cmn_11()
      {
         super();
         addFrameScript(83,this.frame84);
      }
      
      internal function frame84() : *
      {
         this.stop();
      }
   }
}

