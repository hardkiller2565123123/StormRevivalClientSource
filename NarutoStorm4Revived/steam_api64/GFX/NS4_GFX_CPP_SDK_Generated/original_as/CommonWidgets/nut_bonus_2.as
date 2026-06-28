package script.duel_cond
{
   import flash.display.MovieClip;
   import script.xcmn_font.smb_font;
   import script.xcmn_win2.smb_win2;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol21")]
   public class nut_bonus extends MovieClip
   {
      
      public var mc_bns_set01:smb_bns_set;
      
      public var mc_mny_set:MovieClip;
      
      public var mc_tit_set:MovieClip;
      
      public var mc_win:smb_win2;
      
      public var txt_bns_tit01:smb_font;
      
      public function nut_bonus()
      {
         super();
         addFrameScript(0,this.frame1,7,this.frame8,14,this.frame15);
      }
      
      internal function frame1() : *
      {
         this.txt_bns_tit01.SetTextPivot(smb_font.CCD_PIVOT_CC);
         this.txt_bns_tit01.SetTextColor(smb_font.CCD_COLOR_BLACK);
         this.txt_bns_tit01.SetTextSize(30);
      }
      
      internal function frame8() : *
      {
         this.stop();
      }
      
      internal function frame15() : *
      {
         this.stop();
      }
   }
}

