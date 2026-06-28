package script.duel_act
{
   import flash.display.MovieClip;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol19")]
   public dynamic class all_act3_2p extends MovieClip
   {
      
      public var mc_lang_cmn_2p:MovieClip;
      
      public function all_act3_2p()
      {
         super();
         addFrameScript(48,this.frame49,59,this.frame60);
      }
      
      internal function frame49() : *
      {
         gotoAndPlay("loop");
      }
      
      internal function frame60() : *
      {
         stop();
      }
   }
}

