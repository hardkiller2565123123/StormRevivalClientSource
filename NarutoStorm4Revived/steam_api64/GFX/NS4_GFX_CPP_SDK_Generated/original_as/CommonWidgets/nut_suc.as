package script.duel_cond
{
   import flash.display.MovieClip;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol17")]
   public class nut_suc extends MovieClip
   {
      
      public var mc_bg:MovieClip;
      
      public var mc_check:anm_check;
      
      public var mc_suc:MovieClip;
      
      public function nut_suc()
      {
         super();
         addFrameScript(28,this.frame29,39,this.frame40);
      }
      
      internal function frame29() : *
      {
         this.stop();
      }
      
      internal function frame40() : *
      {
         this.stop();
      }
   }
}

