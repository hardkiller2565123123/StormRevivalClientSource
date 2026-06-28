package duel_cond_fla
{
   import flash.display.MovieClip;
   import script.xcmn_win3.smb_win3;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol23")]
   public dynamic class anm_win_6 extends MovieClip
   {
      
      public var mc_title:MovieClip;
      
      public var mc_win:smb_win3;
      
      public function anm_win_6()
      {
         super();
         addFrameScript(0,this.frame1);
      }
      
      internal function frame1() : *
      {
         this.stop();
      }
   }
}

