package script.net_rank
{
   import flash.display.MovieClip;
   import flash.events.Event;
   import flash.external.ExternalInterface;
   import flash.geom.Point;
   import script.net_cmn.smb_win2;
   import script.xcmn_btn_plat.all_btn_plat;
   import script.xcmn_font.smb_font;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol10")]
   public class nut_ranking extends MovieClip
   {
      
      public var all_ranking:nut_rankbar;
      
      public var mc_list_win:smb_win2;
      
      internal var default_x:Number = 0;
      
      internal var default_y:Number = 0;
      
      internal var m_type:Number = 0;
      
      internal var m_scroll:Array = new Array(10);
      
      public function nut_ranking()
      {
         super();
         addFrameScript(5,this.frame6,16,this.frame17);
         this.scrollreset();
      }
      
      public function scrollreset() : *
      {
         this.m_scroll[0] = false;
         this.m_scroll[1] = false;
         this.m_scroll[2] = false;
         this.m_scroll[3] = false;
         this.m_scroll[4] = false;
         this.m_scroll[5] = false;
         this.m_scroll[6] = false;
         this.m_scroll[7] = false;
         this.m_scroll[8] = false;
         this.m_scroll[9] = false;
      }
      
      public function Initialize() : *
      {
         this.all_ranking.all_btn_plat_l.gotoAndStop(all_btn_plat.CCD_BUTTON_L1);
         this.all_ranking.all_btn_plat_r.gotoAndStop(all_btn_plat.CCD_BUTTON_R1);
         this.SetLayer(all_nut.UI_BAR_LAYER_1);
         var _loc1_:Point = new Point();
         this.all_ranking.mc_rankbar00.txt_userid.GetTextPos(_loc1_);
         this.default_x = _loc1_.x;
         this.default_y = _loc1_.y;
      }
      
      public function IsEnd() : Boolean
      {
         if(currentLabel == "end")
         {
            return true;
         }
         return false;
      }
      
      public function IsInput() : Boolean
      {
         if(currentLabel == "loop")
         {
            return true;
         }
         return false;
      }
      
      public function onEnterFrameCtrl(param1:Event) : *
      {
      }
      
      public function PlayOutAnm() : *
      {
         gotoAndPlay("out");
      }
      
      public function SetTextHead(param1:String, param2:int) : *
      {
         switch(param2)
         {
            case all_nut.UI_TEXT_HEAD:
               this.all_ranking.mc_head.txt_sort.SetText(param1);
               break;
            case all_nut.UI_TEXT_HEAD_RANKING:
               this.all_ranking.mc_rank_head.txt_ranking.SetText(param1);
               break;
            case all_nut.UI_TEXT_HEAD_USER_ID:
               this.all_ranking.mc_rank_head.txt_id.SetText(param1);
               break;
            case all_nut.UI_TEXT_HEAD_BP:
               this.all_ranking.mc_rank_head.mc_txt_bp.txt_bp.SetText(param1);
               break;
            case all_nut.UI_TEXT_HEAD_WIN:
               this.all_ranking.mc_rank_head.mc_wins_per.txt_wins.SetText(param1);
               break;
            case all_nut.UI_TEXT_HEAD_WIN_PER:
               this.all_ranking.mc_rank_head.mc_wins_per.txt_per.SetText(param1);
               break;
            case all_nut.UI_TEXT_HEAD_TITLE:
               this.all_ranking.mc_rank_head.mc_txt_title.txt_title.SetText(param1);
         }
      }
      
      public function SetTextSetting(param1:int) : *
      {
         this.m_type = param1;
         var _loc2_:int = 0;
         var _loc3_:int = 0;
         var _loc4_:MovieClip = null;
         var _loc5_:smb_font = null;
         if(this.all_ranking.currentLabel == "lay2")
         {
            _loc3_ = all_nut.UI_RANK_BAR_NUM;
         }
         else
         {
            _loc3_ = all_nut.UI_RANK_BAR_MAX_NUM;
         }
         switch(param1)
         {
            case 0:
               _loc2_ = 0;
               while(_loc2_ < _loc3_)
               {
                  _loc4_ = this.GetMc(_loc2_);
                  if(_loc4_)
                  {
                     _loc5_ = _loc4_.getChildByName("txt_userid") as smb_font;
                     if(_loc5_ != null)
                     {
                        _loc5_.SetTextPivot(smb_font.CCD_PIVOT_CC);
                        _loc5_.SetTextFit(true);
                        _loc5_.SetTextScroll(false);
                        _loc5_.SetTextPos(this.default_x,this.default_y);
                        _loc5_ = null;
                     }
                  }
                  _loc2_++;
               }
               break;
            case 1:
               _loc2_ = 0;
               while(_loc2_ < _loc3_)
               {
                  _loc4_ = this.GetMc(_loc2_);
                  if(_loc4_)
                  {
                     _loc5_ = _loc4_.getChildByName("txt_userid") as smb_font;
                     if(_loc5_ != null)
                     {
                        _loc5_.SetTextPivot(smb_font.CCD_PIVOT_LC);
                        _loc5_.SetTextFit(false);
                        _loc5_.SetTextScroll(true);
                        _loc5_.SetTextPos(this.default_x - 210,this.default_y);
                        _loc5_ = null;
                     }
                  }
                  _loc2_++;
               }
         }
      }
      
      public function GetMc(param1:int) : MovieClip
      {
         var _loc2_:MovieClip = null;
         switch(param1)
         {
            case 0:
               _loc2_ = this.all_ranking.mc_rankbar00;
               break;
            case 1:
               _loc2_ = this.all_ranking.mc_rankbar01;
               break;
            case 2:
               _loc2_ = this.all_ranking.mc_rankbar02;
               break;
            case 3:
               _loc2_ = this.all_ranking.mc_rankbar03;
               break;
            case 4:
               _loc2_ = this.all_ranking.mc_rankbar04;
               break;
            case 5:
               _loc2_ = this.all_ranking.mc_rankbar05;
               break;
            case 6:
               _loc2_ = this.all_ranking.mc_rankbar06;
               break;
            case 7:
               _loc2_ = this.all_ranking.mc_rankbar07;
               break;
            case 8:
               _loc2_ = this.all_ranking.mc_rankbar08;
               break;
            case 9:
               _loc2_ = this.all_ranking.mc_rankbar09;
               break;
            default:
               return null;
         }
         return _loc2_;
      }
      
      public function SetTextBar(param1:String, param2:int, param3:int) : *
      {
         var _loc4_:MovieClip = null;
         if(param3 >= all_nut.UI_RANK_BAR_NUM && this.all_ranking.currentLabel == "lay2")
         {
            return;
         }
         switch(param3)
         {
            case 0:
               _loc4_ = this.all_ranking.mc_rankbar00;
               break;
            case 1:
               _loc4_ = this.all_ranking.mc_rankbar01;
               break;
            case 2:
               _loc4_ = this.all_ranking.mc_rankbar02;
               break;
            case 3:
               _loc4_ = this.all_ranking.mc_rankbar03;
               break;
            case 4:
               _loc4_ = this.all_ranking.mc_rankbar04;
               break;
            case 5:
               _loc4_ = this.all_ranking.mc_rankbar05;
               break;
            case 6:
               _loc4_ = this.all_ranking.mc_rankbar06;
               break;
            case 7:
               _loc4_ = this.all_ranking.mc_rankbar07;
               break;
            case 8:
               _loc4_ = this.all_ranking.mc_rankbar08;
               break;
            case 9:
               _loc4_ = this.all_ranking.mc_rankbar09;
               break;
            default:
               return;
         }
         if(_loc4_ != null)
         {
            switch(param2)
            {
               case all_nut.UI_TEXT_BAR_RANKING:
                  if(_loc4_.txt_ranking_num)
                  {
                     _loc4_.txt_ranking_num.SetText(param1);
                  }
                  break;
               case all_nut.UI_TEXT_BAR_USER_ID:
                  if(_loc4_.txt_userid)
                  {
                     _loc4_.txt_userid.SetText(param1);
                     if(this.m_type == 1)
                     {
                        _loc4_.txt_userid.SetTextFit(false);
                        if(this.m_scroll[param3] == true)
                        {
                           trace("#SetTextBar scroll on");
                           _loc4_.txt_userid.PlayTextScroll();
                        }
                        else
                        {
                           trace("#SetTextBar scroll off");
                           _loc4_.txt_userid.StopTextScroll();
                        }
                        _loc4_.txt_userid.SetTextPivot(smb_font.CCD_PIVOT_LC);
                        _loc4_.txt_userid.SetTextFieldWidth(420);
                     }
                     else
                     {
                        _loc4_.txt_userid.SetTextPivot(smb_font.CCD_PIVOT_CC);
                        _loc4_.txt_userid.SetTextFieldWidth(420);
                     }
                  }
                  break;
               case all_nut.UI_TEXT_BAR_BP:
                  if(_loc4_.txt_bp_num)
                  {
                     _loc4_.txt_bp_num.SetText(param1);
                  }
                  break;
               case all_nut.UI_TEXT_BAR_WINS:
                  if(_loc4_.txt_wins_num)
                  {
                     _loc4_.txt_wins_num.SetText(param1);
                  }
                  break;
               case all_nut.UI_TEXT_BAR_WIN_PER:
                  if(_loc4_.txt_per_num)
                  {
                     _loc4_.txt_per_num.SetText(param1);
                  }
                  break;
               case all_nut.UI_TEXT_BAR_TITLE:
                  if(_loc4_.txt_title)
                  {
                     _loc4_.txt_title.SetText(param1);
                  }
                  break;
               case all_nut.UI_TEXT_BAR_RANK:
                  if(_loc4_.txt_rank_num)
                  {
                     _loc4_.txt_rank_num.SetText(param1);
                  }
            }
         }
      }
      
      public function SelectRankingBar(param1:int, param2:Boolean, param3:int) : *
      {
         var _loc4_:String = null;
         var _loc5_:Boolean = false;
         var _loc6_:MovieClip = null;
         var _loc7_:smb_font = null;
         if(param1 >= all_nut.UI_RANK_BAR_NUM && this.all_ranking.currentLabel == "lay2")
         {
            return;
         }
         if(param1 >= 0 && param1 < all_nut.UI_RANK_BAR_MAX_NUM)
         {
            _loc5_ = false;
            if(param2)
            {
               _loc5_ = true;
               _loc4_ = "on_";
            }
            else
            {
               _loc4_ = "off_";
            }
            switch(param3)
            {
               case all_nut.UI_SORT_TYPE_BP:
                  _loc4_ += "bp";
                  break;
               case all_nut.UI_SORT_TYPE_WINS:
                  _loc4_ += "bp";
                  break;
               case all_nut.UI_SORT_TYPE_CHARA_USE:
                  _loc4_ += "bp";
                  break;
               case all_nut.UI_SORT_TYPE_CHARA_WIN:
                  _loc4_ += "bp";
            }
            switch(param1)
            {
               case 0:
                  this.all_ranking.mc_rankbar00.gotoAndStop(_loc4_);
                  break;
               case 1:
                  this.all_ranking.mc_rankbar01.gotoAndStop(_loc4_);
                  break;
               case 2:
                  this.all_ranking.mc_rankbar02.gotoAndStop(_loc4_);
                  break;
               case 3:
                  this.all_ranking.mc_rankbar03.gotoAndStop(_loc4_);
                  break;
               case 4:
                  this.all_ranking.mc_rankbar04.gotoAndStop(_loc4_);
                  break;
               case 5:
                  this.all_ranking.mc_rankbar05.gotoAndStop(_loc4_);
                  break;
               case 6:
                  this.all_ranking.mc_rankbar06.gotoAndStop(_loc4_);
                  break;
               case 7:
                  this.all_ranking.mc_rankbar07.gotoAndStop(_loc4_);
                  break;
               case 8:
                  this.all_ranking.mc_rankbar08.gotoAndStop(_loc4_);
                  break;
               case 9:
                  this.all_ranking.mc_rankbar09.gotoAndStop(_loc4_);
            }
            _loc6_ = null;
            if(this.m_type == 1)
            {
               _loc7_ = null;
               _loc6_ = this.GetMc(param1);
               if(_loc6_)
               {
                  _loc7_ = _loc6_.getChildByName("txt_userid") as smb_font;
                  if(_loc7_ != null)
                  {
                     if(_loc5_)
                     {
                        this.m_scroll[param1] = true;
                     }
                     else
                     {
                        this.m_scroll[param1] = false;
                     }
                  }
               }
            }
            _loc6_ = this.GetMc(param1);
            if(_loc6_)
            {
               _loc7_ = _loc6_.getChildByName("txt_bp_num") as smb_font;
               if(_loc7_)
               {
                  _loc7_.SetText("");
               }
               _loc7_ = _loc6_.getChildByName("txt_wins_num") as smb_font;
               if(_loc7_)
               {
                  _loc7_.SetText("");
               }
               _loc7_ = _loc6_.getChildByName("txt_per_num") as smb_font;
               if(_loc7_)
               {
                  _loc7_.SetText("");
               }
            }
         }
      }
      
      public function ChangeSortText(param1:int) : *
      {
         switch(param1)
         {
            case all_nut.UI_SORT_TYPE_BP:
               this.all_ranking.gotoAndStop("lay1");
               this.all_ranking.mc_rank_head.gotoAndStop("bp");
               this.all_ranking.mc_rank_head.mc_txt_bp.visible = true;
               this.all_ranking.mc_rank_head.mc_wins_per.visible = false;
               this.all_ranking.mc_rank_head.mc_txt_bp.txt_bp.SetText("");
               this.all_ranking.all_btn_plat_l.visible = true;
               this.all_ranking.all_btn_plat_r.visible = true;
               this.SetTextSetting(0);
               break;
            case all_nut.UI_SORT_TYPE_WINS:
               this.all_ranking.gotoAndStop("lay1");
               this.all_ranking.mc_rank_head.gotoAndStop("bp");
               this.all_ranking.mc_rank_head.mc_txt_bp.visible = true;
               this.all_ranking.mc_rank_head.mc_wins_per.visible = false;
               this.all_ranking.mc_rank_head.mc_txt_bp.txt_bp.SetText("");
               this.all_ranking.all_btn_plat_l.visible = true;
               this.all_ranking.all_btn_plat_r.visible = true;
               this.SetTextSetting(0);
               break;
            case all_nut.UI_SORT_TYPE_CHARA_USE:
               this.all_ranking.gotoAndStop("lay1");
               this.all_ranking.mc_rank_head.gotoAndStop("bp");
               this.all_ranking.mc_rank_head.mc_txt_bp.visible = true;
               this.all_ranking.mc_rank_head.mc_wins_per.visible = false;
               this.all_ranking.mc_rank_head.mc_txt_bp.txt_bp.SetText("");
               this.all_ranking.all_btn_plat_l.visible = false;
               this.all_ranking.all_btn_plat_r.visible = false;
               this.SetTextSetting(1);
               break;
            case all_nut.UI_SORT_TYPE_CHARA_WIN:
               this.all_ranking.gotoAndStop("lay1");
               this.all_ranking.mc_rank_head.gotoAndStop("bp");
               this.all_ranking.mc_rank_head.mc_txt_bp.visible = true;
               this.all_ranking.mc_rank_head.mc_wins_per.visible = false;
               this.all_ranking.mc_rank_head.mc_txt_bp.txt_bp.SetText("");
               this.all_ranking.all_btn_plat_l.visible = false;
               this.all_ranking.all_btn_plat_r.visible = false;
               this.SetTextSetting(1);
         }
      }
      
      public function SetYouIconVisible(param1:int, param2:Boolean) : *
      {
         if(param1 >= all_nut.UI_RANK_BAR_NUM && this.all_ranking.currentLabel == "lay2")
         {
            return;
         }
         var _loc3_:MovieClip = null;
         _loc3_ = this.GetMc(param1);
         if(_loc3_)
         {
            if(param2 == true)
            {
               _loc3_.all_myrank.txt_msg.SetText(String(ExternalInterface.call("MessageConvert","networkmode_681")));
            }
            _loc3_.all_myrank.visible = param2;
         }
      }
      
      public function SetLayer(param1:int) : *
      {
         if(param1 == all_nut.UI_BAR_LAYER_1)
         {
            this.all_ranking.gotoAndStop("lay1");
         }
         else if(param1 == all_nut.UI_BAR_LAYER_2)
         {
            this.all_ranking.gotoAndStop("lay2");
         }
      }
      
      internal function frame6() : *
      {
         stop();
      }
      
      internal function frame17() : *
      {
         stop();
      }
   }
}

