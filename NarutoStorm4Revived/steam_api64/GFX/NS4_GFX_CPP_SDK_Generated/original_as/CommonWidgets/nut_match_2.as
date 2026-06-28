package script.net_match_2
{
   import flash.display.MovieClip;
   import script.xcmn_font.smb_font;
   import script.xcmn_unset.nut_scb_bg;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol9")]
   public dynamic class nut_match_2 extends MovieClip
   {
      
      public var mc_id03:MovieClip;
      
      public var mc_id04:MovieClip;
      
      public var mc_id05:MovieClip;
      
      public var mc_id06:MovieClip;
      
      public var mc_id07:MovieClip;
      
      public var txt_head:smb_font;
      
      public var nut_scb_bg:script.xcmn_unset.nut_scb_bg;
      
      public var mc_id00:MovieClip;
      
      public var mc_wins:MovieClip;
      
      public var mc_id01:MovieClip;
      
      public var mc_id02:MovieClip;
      
      public function nut_match_2()
      {
         super();
         addFrameScript(0,this.frame1,1,this.frame2);
      }
      
      internal function frame1() : *
      {
         stop();
         this.txt_head.SetTextPivot(smb_font.CCD_PIVOT_CC);
         this.txt_head.SetTextColor(15058221);
         this.txt_head.SetDropShadowFilter(smb_font.CCD_COLOR_BLACK);
      }
      
      internal function frame2() : *
      {
         stop();
      }
   }
}

