using SDK.Common;
using UnityEngine.UI;

namespace Game.UI
{
    /**
     * @brief 包裹
     */
    public class UIPack : Form
    {
        public UIPack()
        {

        }

        // 初始化控件
        override public void onReady()
        {
            base.onReady();

            findWidget();
            addEventHandle();
        }

        // 关联窗口
        protected void findWidget()
        {

        }

        protected void addEventHandle()
        {
            
        }
    }
}