package script.duel_act
{
   import flash.display.MovieClip;
   import script.duel_act_lang.smb_lang_fin_r;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol18")]
   public dynamic class all_act2_2p extends MovieClip
   {
      
      public var mc_lang_fin:smb_lang_fin_r;
      
      public function all_act2_2p()
      {
         super();
         addFrameScript(49,this.frame50,57,this.frame58);
      }
      
      internal function frame50() : *
      {
         gotoAndPlay("loop");
      }
      
      internal function frame58() : *
      {
         stop();
      }
   }
}

