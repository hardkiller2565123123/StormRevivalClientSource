package script.duel_cond
{
   import flash.display.MovieClip;
   import script.xcmn_fade.nut_fade_bk2;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol34")]
   public class nut_cond extends MovieClip
   {
      
      public var mc_cond:MovieClip;
      
      public var mc_fade:nut_fade_bk2;
      
      public var mc_win:MovieClip;
      
      public function nut_cond()
      {
         super();
         addFrameScript(7,this.frame8,15,this.frame16);
      }
      
      internal function frame8() : *
      {
         this.stop();
      }
      
      internal function frame16() : *
      {
         this.stop();
      }
   }
}

