package net_card_fla
{
   import flash.display.MovieClip;
   import script.card_txt.nut_rank;
   import script.icon_rarity.nut_rarity;
   import script.net_card.anm_card_skin;
   import script.xcmn_font.smb_font;
   import script.xcmn_tex00.nut_tex00;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol49")]
   public dynamic class anm_card_front_4 extends MovieClip
   {
      
      public var all_card_skin:anm_card_skin;
      
      public var all_rank:nut_rank;
      
      public var all_rarity:nut_rarity;
      
      public var dmy_images:nut_tex00;
      
      public var image_back:MovieClip;
      
      public var mc_card_title:MovieClip;
      
      public var mc_eff00:MovieClip;
      
      public var mc_rank_title:MovieClip;
      
      public var txt_bp:smb_font;
      
      public var txt_bp_num:smb_font;
      
      public var txt_rank:smb_font;
      
      public var txt_region:smb_font;
      
      public var txt_userid:smb_font;
      
      public function anm_card_front_4()
      {
         super();
         addFrameScript(0,this.frame1);
      }
      
      internal function frame1() : *
      {
         this.txt_userid.SetTextPivot(smb_font.CCD_PIVOT_CC);
         this.txt_userid.SetTextColor(smb_font.CCD_COLOR_WHITE);
         this.txt_userid.SetTextSize(28);
         this.txt_userid.SetTextFieldWidth(300);
         this.txt_userid.SetTextFit(true);
         this.txt_region.SetTextPivot(smb_font.CCD_PIVOT_CC);
         this.txt_region.SetTextColor(smb_font.CCD_COLOR_BLACK);
         this.txt_region.SetTextFieldWidth(68);
         this.txt_region.SetTextFit(true);
         this.txt_bp.SetTextPivot(smb_font.CCD_PIVOT_LC);
         this.txt_bp.SetTextColor(smb_font.CCD_COLOR_WHITE);
         this.txt_bp.SetDropShadowFilter(smb_font.CCD_COLOR_BLACK);
         this.txt_bp_num.SetTextPivot(smb_font.CCD_PIVOT_RC);
         this.txt_bp_num.SetTextColor(smb_font.CCD_COLOR_WHITE);
         this.txt_bp_num.SetDropShadowFilter(smb_font.CCD_COLOR_BLACK);
         this.txt_rank.SetTextPivot(smb_font.CCD_PIVOT_CC);
         this.txt_rank.SetTextSize(33);
         this.txt_rank.SetTextColor(smb_font.CCD_COLOR_WHITE);
         this.txt_rank.SetDropShadowFilter(smb_font.CCD_COLOR_BLACK);
         this.txt_rank.SetTextFieldWidth(70);
         this.txt_rank.SetTextFit(true);
      }
   }
}

