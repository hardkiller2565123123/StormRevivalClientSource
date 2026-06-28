package script.net_bingo
{
   import flash.display.MovieClip;
   import flash.external.ExternalInterface;
   import script.icon_new.nut_new;
   import script.icon_result2.smb_rslt_ok;
   import script.xcmn_font.smb_font;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol8")]
   public class anm_list extends MovieClip
   {
      
      public var all_new:nut_new;
      
      public var mc_ok:smb_rslt_ok;
      
      public var txt_comp:smb_font;
      
      public var txt_title:smb_font;
      
      private var m_title:smb_font = null;
      
      private var m_comp:smb_font = null;
      
      private var m_new:nut_new = null;
      
      private var m_getIcon:MovieClip = null;
      
      public function anm_list()
      {
         super();
         addFrameScript(0,this.frame1,1,this.frame2);
         this.m_title = this["txt_title"];
         this.m_comp = this["txt_comp"];
         this.m_new = this["all_new"];
         this.m_getIcon = this["mc_ok"];
         this.m_new.stop();
         this.m_new.visible = false;
      }
      
      public function SetRewardInfo(param1:uint, param2:String, param3:uint, param4:Boolean, param5:int) : *
      {
         var _loc8_:Array = null;
         param1++;
         var _loc6_:Array = new Array();
         _loc6_.push(param2);
         if(this.m_title.IsArabic() == true)
         {
            _loc6_.push(String.fromCharCode(8207) + param5.toString());
         }
         else
         {
            _loc6_.push(param5.toString());
         }
         if(this.m_title)
         {
            this.m_title.SetText(String(ExternalInterface.call("MessageConvert","advStartMenu_007")),_loc6_);
            _loc8_ = new Array();
            _loc8_.push(param1.toString());
            _loc8_.push(this.m_title.GetText());
            this.m_title.SetText(String(ExternalInterface.call("MessageConvert","getting_info_etc_051")),_loc8_);
         }
         else
         {
            trace("#anm_list SetRewardInfo m_title : NULL ");
         }
         if(this.m_comp)
         {
            this.m_comp.SetText(String(ExternalInterface.call("MessageConvert","network_sys_199")));
         }
         else
         {
            trace("#anm_list SetRewardInfo m_comp : NULL ");
         }
         var _loc7_:Array = new Array();
         _loc7_.push(param3.toString());
         if(this.m_comp)
         {
            this.m_comp.ReplaceTextList(_loc7_);
         }
         else
         {
            trace("#anm_list SetRewardInfo m_comp : NULL ");
         }
         if(this.m_getIcon)
         {
            this.m_getIcon.visible = param4;
         }
         else
         {
            trace("#anm_list SetRewardInfo m_getIcon : NULL ");
         }
      }
      
      internal function frame1() : *
      {
         stop();
         this.txt_title.SetTextPivot(smb_font.CCD_PIVOT_CC);
         this.txt_title.SetTextColor(469645);
         this.txt_title.SetDropShadowFilter(11645361);
         this.txt_title.SetTextFieldWidth(970);
         this.txt_title.SetTextFit(true);
         this.txt_comp.SetTextPivot(smb_font.CCD_PIVOT_CC);
         this.txt_comp.SetTextColor(469645);
         this.txt_comp.SetDropShadowFilter(11645361);
         this.txt_comp.SetTextFieldWidth(970);
         this.txt_comp.SetTextFit(true);
      }
      
      internal function frame2() : *
      {
         stop();
         this.txt_title.SetTextPivot(smb_font.CCD_PIVOT_CC);
         this.txt_title.SetTextColor(smb_font.CCD_COLOR_WHITE);
         this.txt_title.DisableDropShadowFilter();
         this.txt_title.SetTextFieldWidth(970);
         this.txt_title.SetTextFit(true);
         this.txt_comp.SetTextPivot(smb_font.CCD_PIVOT_CC);
         this.txt_comp.SetTextColor(smb_font.CCD_COLOR_WHITE);
         this.txt_comp.DisableDropShadowFilter();
         this.txt_comp.SetTextFieldWidth(970);
         this.txt_comp.SetTextFit(true);
      }
   }
}

